/**
 * @file    wm_uart_timer.c
 *
 * @brief   Timer for uart Module
 *
 * @author  dave
 *
 * Copyright (c) 2015 Winner Microelectronics Co., Ltd.
 */

#include <string.h>

#include "wm_regs.h"
#include "wm_type_def.h"
#include "wm_timer.h"
#include "wm_uart_task.h"
#include "wm_osal.h"
#include "wm_irq.h"
#include "wm_wl_task.h"

#if (TLS_CONFIG_HOSTIF && TLS_CONFIG_UART)
extern void uart_rx(struct tls_uart *uart);
extern struct task_parameter wl_task_param_hostif;

static u8 uart_tmid = WM_TIMER_ID_INVALID;

void tls_timer2_stop(void)
{
    if (uart_tmid != WM_TIMER_ID_INVALID)
    {
        tls_timer_destroy(uart_tmid);
        uart_tmid = WM_TIMER_ID_INVALID;
    }
}

static void tls_timer2_isr(void *p)
{
    struct tls_uart *uart;

    uart = (struct tls_uart *)p;
    tls_timer2_stop();
    uart->rx_idle = TRUE;
    tls_wl_task_callback_static(&wl_task_param_hostif, (start_routine) uart_rx,
                                uart, 0, TLS_MSG_ID_UART_RX);
}

void tls_timer2_start(struct tls_uart *uart, u32 timeout)
{
    struct tls_timer_cfg cfg;

    memset(&cfg, 0, sizeof(cfg));
    cfg.callback  = tls_timer2_isr;
    cfg.arg       = uart;
    cfg.is_repeat = FALSE;
    cfg.unit = TLS_TIMER_UNIT_US;

    cfg.timeout = timeout;

    uart_tmid = tls_timer_create(&cfg);
    tls_timer_start(uart_tmid);
}
#endif
