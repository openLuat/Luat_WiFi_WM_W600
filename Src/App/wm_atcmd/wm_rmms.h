/*-------------------------------------------------------------------------
Copyright 2007-2010 CEC Huada Electronic  Design Co., Ltd.
This file is part of Huada Wireless Lan software.
File name:	mms.h
Author:		wangyf
Version:		V1.0.0
Date:		2010-5-27
Description:	
Others:		
  
Revision History:	
Who         When          What
--------    ----------    ----------------------------------------------
  
-------------------------------------------------------------------------*/
#ifndef __RMMS_H__
#define __RMMS_H__

#if TLS_CONFIG_RMMS
#if (GCC_COMPILE==1)
#include "wm_cmdp_hostif_gcc.h"
#else
#include "wm_cmdp_hostif.h"
#endif
#define RMMS_LISTERN_PORT   988

#define RMMS_ERR_SUCCESS         0
#define RMMS_ERR_LINKDOWN       -1
#define RMMS_ERR_PARAM          -2
#define RMMS_ERR_MEM            -3
#define RMMS_ERR_NOT_BIND       -4
#define RMMS_ERR_NOT_FOUND      -5
#define RMMS_ERR_INACTIVE       -6


s8 RMMS_Init(const struct netif *Netif);
void RMMS_Fini(void);
void RMMS_SendHedAtRsp(struct rmms_msg *Msg);
#endif

#endif

