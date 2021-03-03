/* Include standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

volatile BaseType_t xInsideInterrupt = pdFALSE;

/* Provide a main function for the build to succeed. */
int main()
{
    return 0;
}

void FreeRTOS_PrintARPCache( void )
{
}

const char * FreeRTOS_GetTCPStateName( UBaseType_t ulState )
{
}

void vApplicationPingReplyHook( ePingReplyStatus_t eStatus,
  	                                    uint16_t usIdentifier )
{
}

BaseType_t FreeRTOS_SendPingRequest( uint32_t ulIPAddress,
  	                                         size_t uxNumberOfBytesToSend,
  	                                         TickType_t uxBlockTimeTicks )
{
}

eFrameProcessingResult_t prvProcessICMPMessage_IPv6( NetworkBufferDescriptor_t * const pxNetworkBuffer )
{
}

uint32_t ulDNSHandlePacket( const NetworkBufferDescriptor_t * pxNetworkBuffer )
{
}

BaseType_t xApplicationDNSQueryHook( struct xNetworkEndPoint * pxEndPoint,
                                               const char * pcName )
{
}

void vDNSInitialise( void )
{
}

size_t xPortGetMinimumEverFreeHeapSize( void )
{
    return 0;
}

const char * pcApplicationHostnameHook( void )
{
}

uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
{
}

BaseType_t xNetworkInterfaceInitialise( void )
{
}

void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent,
                                             struct xNetworkEndPoint * pxEndPoint )
{
}

BaseType_t xApplicationGetRandomNumber( uint32_t * pulNumber )
{
}
void vApplicationDaemonTaskStartupHook( void )
{
}
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
}
void vPortDeleteThread( void * pvTaskToDelete )
{
}
void vApplicationIdleHook( void )
{
}
void vApplicationTickHook( void )
{
}
unsigned long ulGetRunTimeCounterValue( void )
{
}
void vPortEndScheduler( void )
{
}
BaseType_t xPortStartScheduler( void )
{
}
void vPortEnterCritical( void )
{
}
void vPortExitCritical( void )
{
}

void * pvPortMalloc( size_t xWantedSize )
{
    return malloc( xWantedSize );
}

void vPortFree( void * pv )
{
    free( pv );
}

StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     TaskFunction_t pxCode,
                                     void * pvParameters )
{
}
void vPortGenerateSimulatedInterrupt( uint32_t ulInterruptNumber )
{
}
void vPortCloseRunningThread( void * pvTaskToDelete,
                              volatile BaseType_t * pxPendYield )
{
}
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
}
void vConfigureTimerForRunTimeStats( void )
{
}


BaseType_t xNetworkInterfaceOutput( NetworkBufferDescriptor_t * const pxNetworkBuffer,
                                    BaseType_t bReleaseAfterSend )
{
    return pdPASS;
}
/*-----------------------------------------------------------*/
