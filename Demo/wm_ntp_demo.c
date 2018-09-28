/**
 * @file    wm_ntp_demo.c
 *
 * @brief   ntp demo function
 *
 * @author  dave
 *
 * Copyright (c) 2015 Winner Microelectronics Co., Ltd.
 */

#include "wm_include.h"
#include <string.h>
#include <time.h>
#include "wm_rtc.h"
#include "wm_ntp.h"
#include "wm_demo.h"

#if DEMO_NTP
extern const char DEMO_SET_NTP_S[];
u8 net_status = 0;

static void ntp_demo_net_status_changed_event(u8 status )
{
	switch(status)
	{
		case NETIF_WIFI_JOIN_FAILED:
			net_status = 0;
			break;
		case NETIF_WIFI_JOIN_SUCCESS:

			break;
		case NETIF_IP_NET_UP:
			net_status = 1;
			break;
		default:
			break;
	}
}

int ntp_demo(void)
{
    unsigned int t;	//日历时间相对时间，1970到现在的相对时间
    struct tm *tblock;
    struct tls_ethif * ethif = tls_netif_get_ethif();

    if(ethif->status)	//已经在网
    {
        net_status = 1;
    }
    else
    {
        struct tls_param_ip ip_param;

        tls_param_get(TLS_PARAM_ID_IP, &ip_param, TRUE);
        ip_param.dhcp_enable = TRUE;
        tls_param_set(TLS_PARAM_ID_IP, &ip_param, TRUE);
        tls_wifi_set_oneshot_flag(1);		/*一键配置使能*/
        printf("\n ntp wait one shot......\n");
    }

    tls_netif_add_status_event(ntp_demo_net_status_changed_event);

    while(!net_status)
    {
        tls_os_time_delay(50);
    }

    t = tls_ntp_client();

    printf("now Time :   %s\n", ctime(&t));
    tblock=localtime(&t);	//把日历时间转换成本地时间，已经加上与世界时间8小时的偏差,以1900为基准
    //printf(" sec=%d,min=%d,hour=%d,mon=%d,year=%d\n",tblock->tm_sec,tblock->tm_min,tblock->tm_hour,tblock->tm_mon,tblock->tm_year);
    tls_set_rtc(tblock);

    return WM_SUCCESS;
}


int ntp_set_server_demo(char *ipaddr1, char *ipaddr2, char *ipaddr3)
{
    int server_no = 0;
    printf("\n ipaddr1=%x,2=%x,3=%x\n", ipaddr1, ipaddr2, ipaddr3);
    if (ipaddr1)
    {
        tls_ntp_set_server(ipaddr1, server_no++);
        printf("ntp server %d:%s\n",server_no, ipaddr1);
    }
    if (ipaddr2)
    {
        tls_ntp_set_server(ipaddr2, server_no ++);
        printf("ntp server %d:%s\n",server_no, ipaddr2);
    }
    if (ipaddr3)
    {
        tls_ntp_set_server(ipaddr3, server_no ++);
        printf("ntp server %d:%s\n",server_no, ipaddr3);
    }   

    return WM_SUCCESS;
}

int ntp_query_cfg(void)
{
	tls_ntp_query_sntpcfg();

	return WM_SUCCESS;
}

#endif
