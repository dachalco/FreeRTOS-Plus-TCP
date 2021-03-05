/*
 * FreeRTOS Kernel V10.4.3
 * Copyright 2020 Cambridge Consultants Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 * 1 tab == 4 spaces!
 */


#ifndef PORTMACRO_H
#define PORTMACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE	unsigned long
#define portBASE_TYPE	long
#define portPOINTER_SIZE_TYPE intptr_t

typedef portSTACK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

typedef unsigned long TickType_t;
#define portMAX_DELAY ( TickType_t ) ULONG_MAX

#define portTICK_TYPE_IS_ATOMIC 1

/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define portSTACK_GROWTH			( -1 )
#define portHAS_STACK_OVERFLOW_CHECKING	( 1 )
#define portTICK_PERIOD_MS			( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICK_RATE_MICROSECONDS	( ( portTickType ) 1000000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT			8
/*-----------------------------------------------------------*/

/* Scheduler utilities. */
#define portYIELD()

#define portEND_SWITCHING_ISR( xSwitchRequired )
#define portYIELD_FROM_ISR( x )
/*-----------------------------------------------------------*/

/* Critical section management. */
#define portSET_INTERRUPT_MASK()
#define portCLEAR_INTERRUPT_MASK()

#define portSET_INTERRUPT_MASK_FROM_ISR()  0
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)
#define portDISABLE_INTERRUPTS()
#define portENABLE_INTERRUPTS()
#define portENTER_CRITICAL()
#define portEXIT_CRITICAL()

#define portRECORD_READY_PRIORITY(a,b) (b) |= (1UL<<a)
#define portRESET_READY_PRIORITY(a,b) (b) &= ~(1UL<<a)
/*-----------------------------------------------------------*/

#define portPRE_TASK_DELETE_HOOK( pvTaskToDelete, pxPendYield )
#define portCLEAN_UP_TCB( pxTCB )
/*-----------------------------------------------------------*/

#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )
/*-----------------------------------------------------------*/

/*
 * Tasks run in their own pthreads and context switches between them
 * are always a full memory barrier. ISRs are emulated as signals
 * which also imply a full memory barrier.
 *
 * Thus, only a compilier barrier is needed to prevent the compiler
 * reordering.
 */
#define portMEMORY_BARRIER() __asm volatile( "" ::: "memory" )

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() /* no-op */
#define portGET_RUN_TIME_COUNTER_VALUE()         0

#define portGET_HIGHEST_PRIORITY(a,b)    10
#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */
