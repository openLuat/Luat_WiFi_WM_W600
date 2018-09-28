@;/*
@;    FreeRTOS V7.0.2 - Copyright (C) 2011 Real Time Engineers Ltd.
@;	
@;
@;    ***************************************************************************
@;     *                                                                       *
@;     *    FreeRTOS tutorial books are available in pdf and paperback.        *
@;     *    Complete, revised, and edited pdf reference manuals are also       *
@;     *    available.                                                         *
@;     *                                                                       *
@;     *    Purchasing FreeRTOS documentation will not only help you, by       *
@;     *    ensuring you get running as quickly as possible and with an        *
@;     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
@;     *    the FreeRTOS project to continue with its mission of providing     *
@;     *    professional grade, cross platform, de facto standard solutions    *
@;     *    for microcontrollers - completely free of charge!                  *
@;     *                                                                       *
@;     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
@;     *                                                                       *
@;     *    Thank you for using FreeRTOS, and thank you for your support!      *
@;     *                                                                       *
@;    ***************************************************************************
@;
@;
@;    This file is part of the FreeRTOS distribution.
@;
@;    FreeRTOS is free software; you can redistribute it and/or modify it under
@;    the terms of the GNU General Public License (version 2) as published by the
@;    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
@;    >>>NOTE<<< The modification to the GPL is included to allow you to
@;    distribute a combined work that includes FreeRTOS without being obliged to
@;    provide the source code for proprietary components outside of the FreeRTOS
@;    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
@;    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
@;    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
@;    more details. You should have received a copy of the GNU General Public
@;    License and the FreeRTOS license exception along with FreeRTOS; if not it
@;    can be viewed here: http://www.freertos.org/a00114.html and also obtained
@;    by writing to Richard Barry, contact details for whom are available on the
@;    FreeRTOS WEB site.
@;
@;    1 tab == 4 spaces!
@;
@;    http://www.FreeRTOS.org - Documentation, latest information, license and
@;    contact details.
@;
@;    http://www.SafeRTOS.com - A version that is certified for use in safety
@;    critical systems.
@;
@;    http://www.OpenRTOS.com - Commercial support, development, porting,
@;    licensing and training services.
@;*/

	.include "../../../Include/wm_config_gcc.inc"
.section .text  
.ifdef __TLS_OS_FREERTOS
	.extern	vTaskSwitchContext
	.extern	vTaskIncrementTick
	.extern	OS_CPU_IRQ_ISR_Handler
	.extern  ulCriticalNesting		
	.extern	pxCurrentTCB			


	.global	SWI_Handler
	.global	vPortStartFirstTask
	.global	vPreemptiveTick
	.global	vPortYield
	.global	OS_CPU_Tick_ISR
	.global	portDISABLE_INTERRUPTS
	.global	portENABLE_INTERRUPTS

.macro portRESTORE_CONTEXT
	LDR		R0, =pxCurrentTCB		@; Set the LR to the task stack.  The location was...
	LDR		R0, [R0]				@; ... stored in pxCurrentTCB
	LDR		LR, [R0]

	LDR		R0, =ulCriticalNesting	@; The critical nesting depth is the first item on... 
	LDMFD	LR!, {R1}				@; ...the stack.  Load it into the ulCriticalNesting var.
	STR		R1, [R0]				@;

	LDMFD	LR!, {R0}				@; Get the SPSR from the stack.
	MSR		SPSR_cxsf, R0			@;

	LDMFD	LR, {R0-R14}^			@; Restore all system mode registers for the task.
	NOP								@;

	LDR		LR, [LR, #+60]			@; Restore the return address

									@; And return - correcting the offset in the LR to obtain ...
	SUBS	PC, LR, #4				@; ...the correct address.

.endm

.macro portSAVE_CONTEXT
	STMDB 	SP!, {R0}				@; Store R0 first as we need to use it.

	STMDB	SP,{SP}^				@; Set R0 to point to the task stack pointer.
	NOP								@;
	SUB		SP, SP, #4				@;
	LDMIA	SP!,{R0}				@;

	STMDB	R0!, {LR}				@; Push the return address onto the stack.
	MOV		LR, R0					@; Now we have saved LR we can use it instead of R0.
	LDMIA	SP!, {R0}				@; Pop R0 so we can save it onto the system mode stack.

	STMDB	LR,{R0-LR}^				@; Push all the system mode registers onto the task stack.
	NOP								@;
	SUB		LR, LR, #60				@;

	MRS		R0, SPSR				@; Push the SPSR onto the task stack.
	STMDB	LR!, {R0}				@;

	LDR		R0, =ulCriticalNesting	@;
	LDR		R0, [R0]				@;
	STMDB	LR!, {R0}				@;

	LDR		R0, =pxCurrentTCB		@; Store the new top of stack for the task.
	LDR		R1, [R0]				@; 		 
	STR		LR, [R1]				@;

.endm


@;RESTORE portRESTORE_CONTEXT
@;SAVE	portSAVE_CONTEXT

@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@; Starting the first task is done by just restoring the context 
@; setup by pxPortInitialiseStack
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
vPortStartFirstTask:

	@PRESERVE8

	portRESTORE_CONTEXT

vPortYield:

	@PRESERVE8

	@SVC 0
	SWI 0
	bx lr

@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@; Interrupt service routine for the SWI interrupt.  The vector table is
@; configured in the startup.s file.
@;
@; vPortYieldProcessor() is used to manually force a context switch.  The
@; SWI interrupt is generated by a call to taskYIELD() or portYIELD().
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SWI_Handler:

	@PRESERVE8

@	; Within an IRQ ISR the link register has an offset from the true return 
@	; address, but an SWI ISR does not.  Add the offset manually so the same 
@	; ISR return code can be used in both cases.
	ADD	LR, LR, #4

@	; Perform the context switch.
	portSAVE_CONTEXT					@; Save current task context				
	LDR R0, =vTaskSwitchContext			@; Get the address of the context switch function
	MOV LR, PC							@; Store the return address
	BX	R0								@; Call the contedxt switch function
	portRESTORE_CONTEXT					@; restore the context of the selected task	



@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@; Interrupt service routine for preemptive scheduler tick timer
@; Only used if portUSE_PREEMPTION is set to 1 in portmacro.h
@;
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

vPreemptiveTick:

@	PRESERVE8

	portSAVE_CONTEXT					@; Save the context of the current task.	

	LDR R0, =vTaskIncrementTick			@; Increment the tick count.  
	MOV LR, PC							@; This may make a delayed task ready
	BX R0								@; to run.
	
	LDR R0, =vTaskSwitchContext			@; Find the highest priority task that 
	MOV LR, PC							@; is ready to run.
	BX R0
	
	portRESTORE_CONTEXT					@; Restore the context of the highest 
										@; priority task that is ready to run.


@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@; IRQ handler
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
OS_CPU_Tick_ISR:
	@PRESERVE8
	portSAVE_CONTEXT                        @; Save the context of the current task...
                        
	BL     OS_CPU_IRQ_ISR_Handler
                        
	portRESTORE_CONTEXT                     @; Restore the context of the selected task.
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

portDISABLE_INTERRUPTS:
	@PRESERVE8
	STMDB SP!,{R0}
REDISABLE:
	MRS	R0,CPSR	
	ORR R0,R0,#0xc0
	MSR CPSR_cxsf,R0
	MRS R0,CPSR
	AND R0,R0,#0xc0
	CMP R0,#0xc0
	BNE REDISABLE
	LDMIA SP!,{R0}
	BX LR

portENABLE_INTERRUPTS:
	@PRESERVE8
	STMDB SP!,{R0}
	MRS	R0,CPSR	
	BIC R0,R0,#0xc0
	MSR CPSR_cxsf,R0
	LDMIA SP!,{R0}
	BX LR
@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	

	@END
.endif
.end

	
