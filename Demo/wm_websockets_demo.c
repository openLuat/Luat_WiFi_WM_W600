#include "wm_include.h"

#if DEMO_WEBSOCKETS
#include "libwebsockets.h"

char stk_buf[2048*4];
static int longlived = 0;

#define WS_TEST_SRV_ADD	"192.168.10.15"
#define WS_TEST_PORT 	4530
enum demo_protocols {

	PROTOCOL_DUMB_INCREMENT,

	/* always last */
	DEMO_PROTOCOL_COUNT
};
static volatile int force_exit = 0;
static int was_closed;

static int
callback_dumb_increment(struct lws *wsi,
			enum lws_callback_reasons reason,
					       void *user, void *in, size_t len)

{
	int ret = 0;
	char * out = NULL;
	//lwsl_notice("callback_dumb_increment get called with reason %d\n", reason);
	
	switch (reason) {

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		lwsl_info("callback_dumb_increment: LWS_CALLBACK_CLIENT_ESTABLISHED\n");
		break;

	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		lwsl_info("LWS_CALLBACK_CLIENT_CONNECTION_ERROR\n");
		was_closed = 1;
		break;

	case LWS_CALLBACK_CLOSED:
		lwsl_info("LWS_CALLBACK_CLOSED\n");
		was_closed = 1;
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:
		((char *)in)[len] = '\0';
		lwsl_info("rx %d '%s'\n", (int)len, (char *)in);
	//	do_websocket_data();
		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:
		out = tls_mem_alloc(14 + LWS_SEND_BUFFER_PRE_PADDING + LWS_SEND_BUFFER_POST_PADDING);
		if(NULL == out)
			break;
		memset(out, 0, 14 + LWS_SEND_BUFFER_PRE_PADDING + LWS_SEND_BUFFER_POST_PADDING);
		memcpy(out + LWS_SEND_BUFFER_PRE_PADDING, "hello server!", 13);
		ret = lws_write(wsi, out + LWS_SEND_BUFFER_PRE_PADDING, 13, LWS_WRITE_TEXT);
		
		printf("lws_write ret %d \n", ret);
		tls_mem_free(out);

		break;

	default:
		break;
	}

	return 0;
}

static struct lws_protocols protocols[] = {
	{
		"dumb-increment-protocol",//"dumb-increment-protocol,fake-nonexistant-protocol",
		callback_dumb_increment,
		0,
		20,
	},
	{ NULL, NULL, 0, 0 } /* end */
};

int test_websocket_client(void)
{
	int n = 0;
	int ret = 0;
	int port = WS_TEST_PORT;
	int use_ssl;
	struct lws_context *context;
	const char *address;
	struct lws *wsi_dumb, *wsi_hfiot;
	int ietf_version = -1; /* latest */
	struct lws_context_creation_info info;

	lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO | LLL_DEBUG | LLL_PARSER | LLL_HEADER | LLL_CLIENT, NULL);

	memset(&info, 0, sizeof info);

	use_ssl = 1;
	ietf_version = 13/*atoi(optarg)*/;
	longlived = 1;
	address = WS_TEST_SRV_ADD/*argv[optind]*/;

	/*
	 * create the websockets context.  This tracks open connections and
	 * knows how to route any traffic and which protocol version to use,
	 * and if each connection is client or server side.
	 *
	 * For this client-only demo, we tell it to not listen on any port.
	 */
	if(use_ssl)
	{
		info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
	}
	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.max_http_header_pool = 2;

	lwsl_info("callback %x\n", protocols[PROTOCOL_DUMB_INCREMENT].callback);

	context = lws_create_context(&info);
	if (context == NULL) {
		lwsl_err("Creating lws context failed\n");
		return 1;
	}
	was_closed = 0;
#if 1
	/* create a client websocket using dumb increment protocol */
	wsi_dumb = lws_client_connect(context, address, port, use_ssl,
				"/", address, address,
				 protocols[PROTOCOL_DUMB_INCREMENT].name, ietf_version);
	
	if (wsi_dumb == NULL) {
		lwsl_err("lws connect failed\n");
		ret = 1;
		goto bail;
	}
	
	lwsl_info("Waiting for connect...\n");
#endif


	/*
	 * sit there servicing the websocket context to handle incoming
	 * packets, and drawing random circles on the mirror protocol websocket
	 * nothing happens until the client websocket connection is
	 * asynchronously established
	 */

	n = 0;
	while (n >= 0 && !was_closed && !force_exit) {
		lws_callback_on_writable(wsi_dumb);

		n = lws_service(context, 1000);
		printf("lws_service ret %d \n", n);
		if (n < 0)
			continue;
		tls_os_time_delay(HZ);
	}

bail:

	lws_context_destroy(context);

	return ret;

}


u8 bns = 0;
static void bnb(u8 status)
{
	struct tls_ethif * ethif;
	switch(status)
	{
		case NETIF_IP_NET_UP:
#if 1
			ethif = tls_netif_get_ethif();
            printf("net up ==> ip = %d.%d.%d.%d\n",ip4_addr1(&ethif->ip_addr),ip4_addr2(&ethif->ip_addr),
		                     ip4_addr3(&ethif->ip_addr),ip4_addr4(&ethif->ip_addr));
#endif
			bns = 1;
			break;
		default:
			break;
	}
}

void s_task(void *arg)
{
	struct tls_ethif * ethif = NULL;
	u8 *mac = wpa_supplicant_get_mac();
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
		mac[0],
		mac[1],
		mac[2],
		mac[3],
		mac[4],
		mac[5]);	
	tls_netif_add_status_event(bnb);

	ethif = tls_netif_get_ethif();
	if(ethif->status)
		bns = 1;
	while(!bns){
		tls_os_time_delay(5);
	}
	while(1)
	{
		test_websocket_client();
		tls_os_time_delay(HZ);
	}
}


void CreateWebSocketsTask(void)
{
	printf("Image Built:%s %s\r\n", __DATE__, __TIME__);
	
	tls_os_task_create(NULL, NULL, s_task, NULL, stk_buf, sizeof(stk_buf), DEMO_WEBSOCKETS_TASK_PRIO, 0);

}
#endif

