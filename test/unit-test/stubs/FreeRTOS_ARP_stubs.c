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

/* This value should be false for BufferAllocation_2.c */
const BaseType_t xBufferAllocFixedSize = pdFALSE;

UDPPacketHeader_t xDefaultPartUDPPacketHeader =
{
    /* .ucBytes : */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* Ethernet source MAC address. */
        0x08, 0x00,                          /* Ethernet frame type. */
        0x45,                                /* ucVersionHeaderLength. */
        0x00,                                /* ucDifferentiatedServicesCode. */
        0x00, 0x00,                          /* usLength. */
        0x00, 0x00,                          /* usIdentification. */
        0x00, 0x00,                          /* usFragmentOffset. */
        128,                                 /* ucTimeToLive */
        17,                                  /* ucProtocol. */
        0x00, 0x00,                          /* usHeaderChecksum. */
        0x00, 0x00, 0x00, 0x00               /* Source IP address. */
    }
};

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
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
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
