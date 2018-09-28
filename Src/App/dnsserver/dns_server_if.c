/**************************************************************************
 * File Name                  : dns_server.c
 * Author                      :
 * Version                     :
 * Date                         :
 * Description                :
 *
 * Copyright (c) 2014 Winner Microelectronics Co., Ltd. 
 * All rights reserved.
 *
 ***************************************************************************/
#include "wm_type_def.h"
#include "wm_netif.h"
#include "lwip/udp.h"
#include "dns_server.h"
#if TLS_CONFIG_AP
/*************************************************************************** 
* Function: tls_dnss_start 
* Description: start the dns server's service.
* 
* Input: dnsname: specify the server's dns name
* 
* Output: None
* 
* Return: WM_SUCCESS - successfully
*         WM_FAILED  - falied
* 
* Date : 2014-6-10  
****************************************************************************/ 
s8 tls_dnss_start(u8 *dnsname)
{
    s8 ret;
    struct netif *nif = tls_get_netif();

    ret = DNSS_Start(nif, dnsname);
    if (DNSS_ERR_SUCCESS == ret)
        ret = WM_SUCCESS;
    else
        ret = WM_FAILED;

    return ret;
}

/*************************************************************************** 
* Function: tls_dnss_stop 
* Description: stop the dns server's service.
* 
* Input: None
* 
* Output: None
* 
* Return: None
* 
* Date : 2014-6-10  
****************************************************************************/ 
void tls_dnss_stop(void)
{
    DNSS_Stop();
}
#endif
