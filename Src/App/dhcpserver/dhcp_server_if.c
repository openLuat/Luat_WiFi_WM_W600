/**************************************************************************
 * File Name                   : dhcp_server.c
 * Author                       :
 * Version                      :
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
#include "lwip/dns.h"
#include "dhcp_server.h"
#if TLS_CONFIG_AP
/*************************************************************************** 
* Function: tls_dhcps_start 
* Description: Start dhcp server for a network interface.
* 
* Input: None
* 
* Output: None
* 
* Return:     WM_SUCCESS - successfully
*             WM_FAILED  - falied
* 
* Date : 2014-6-10  
****************************************************************************/
s8 tls_dhcps_start(void)
{
    s8 ret;
    struct netif *nif = tls_get_netif();
#if TLS_CONFIG_APSTA
    u8 mode;
    tls_param_get(TLS_PARAM_ID_WPROTOCOL, (void* )&mode, FALSE);
    if (IEEE80211_MODE_APSTA == mode)
        ret = DHCPS_Start(nif->next);
    else
#endif
        ret = DHCPS_Start(nif);

    if (DHCPS_ERR_SUCCESS == ret)
        ret = WM_SUCCESS;
    else
        ret = WM_FAILED;

    return ret;
}

/*************************************************************************** 
* Function: tls_dhcps_stop 
* Description: disable dhcp server.
* 
* Input: None
* 
* Output: None
* 
* Return: None
* 
* Date : 2014-6-10  
****************************************************************************/
void tls_dhcps_stop(void)
{
    DHCPS_Stop();
}

/*************************************************************************** 
* Function: tls_dhcps_getip
* Description: get station's ip address by mac address.
* 
* Input: mac    station's mac address
* 
* Output: None
* 
* Return: ip_addr   station's ip address
* 
* Date : 2015-3-20
****************************************************************************/
ip_addr_t *tls_dhcps_getip(const u8 *mac)
{
	return DHCPS_GetIpByMac(mac);
}

/*************************************************************************** 
* Function: tls_dhcps_setdns
* Description: set dhcp server's dns address.
* 
* Input:  numdns:     the index of the DNS server to set must be 0 or 1(numdns 0/1  --> dns 1/2)
* 
* Output: None
* 
* Return: None
* 
* Date : 2015-3-10
****************************************************************************/
void tls_dhcps_setdns(u8 numdns)
{
    ip_addr_t *dns;
	dns = dns_getserver(numdns);
	DHCPS_SetDns(numdns, dns->addr);

	return;
}

#endif
