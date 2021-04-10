/* Include Unity header */
#include <unity.h>

/* Include standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
#include "queue.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

const BaseType_t xBufferAllocFixedSize = pdFALSE;
volatile BaseType_t xInsideInterrupt = pdFALSE;

/** @brief The expected IP version and header length coded into the IP header itself. */
#define ipIP_VERSION_AND_HEADER_LENGTH_BYTE    ( ( uint8_t ) 0x45 )

const MACAddress_t xLLMNR_MacAddress;

typedef struct QueuePointers
{
    int8_t * pcTail;     /*< Points to the byte at the end of the queue storage area.  Once more byte is allocated than necessary to store the queue items, this is used as >
    int8_t * pcReadFrom; /*< Points to the last place that a queued item was read from when the structure is used as a queue. */
} QueuePointers_t;

typedef struct SemaphoreData
{
    TaskHandle_t xMutexHolder;        /*< The handle of the task that holds the mutex. */
    UBaseType_t uxRecursiveCallCount; /*< Maintains a count of the number of times a recursive mutex has been recursively 'taken' when the structure is used as a mutex. */
} SemaphoreData_t;

/*
 * Definition of the queue used by the scheduler.
 * Items are queued by copy, not reference.  See the following link for the
 * rationale: https://www.FreeRTOS.org/Embedded-RTOS-Queues.html
 */
typedef struct QueueDefinition /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    int8_t * pcHead;           /*< Points to the beginning of the queue storage area. */
    int8_t * pcWriteTo;        /*< Points to the free next place in the storage area. */

    union
    {
        QueuePointers_t xQueue;     /*< Data required exclusively when this structure is used as a queue. */
        SemaphoreData_t xSemaphore; /*< Data required exclusively when this structure is used as a semaphore. */
    } u;

    List_t xTasksWaitingToSend;             /*< List of tasks that are blocked waiting to post onto this queue.  Stored in priority order. */
    List_t xTasksWaitingToReceive;          /*< List of tasks that are blocked waiting to read from this queue.  Stored in priority order. */

    volatile UBaseType_t uxMessagesWaiting; /*< The number of items currently in the queue. */
    UBaseType_t uxLength;                   /*< The length of the queue defined as the number of items it will hold, not the number of bytes. */
    UBaseType_t uxItemSize;                 /*< The size of each items that the queue will hold. */

    volatile int8_t cRxLock;                /*< Stores the number of items received from the queue (removed from the queue) while the queue was locked.  Set to queueUNLOCKE */
    volatile int8_t cTxLock;                /*< Stores the number of items transmitted to the queue (added to the queue) while the queue was locked.  Set to queueUNLOCKED w> */

    #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
        uint8_t ucStaticallyAllocated; /*< Set to pdTRUE if the memory used by the queue was statically allocated to ensure no attempt is made to free the memory. */
    #endif

    #if ( configUSE_QUEUE_SETS == 1 )
        struct QueueDefinition * pxQueueSetContainer;
    #endif

    #if ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t uxQueueNumber;
        uint8_t ucQueueType;
    #endif
} xQUEUE;



UDPPacketHeader_t xDefaultPartUDPPacketHeader =
{
    /* .ucBytes : */
    {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66,  /* Ethernet source MAC address. */
        0x08, 0x00,                          /* Ethernet frame type. */
        ipIP_VERSION_AND_HEADER_LENGTH_BYTE, /* ucVersionHeaderLength. */
        0x00,                                /* ucDifferentiatedServicesCode. */
        0x00, 0x00,                          /* usLength. */
        0x00, 0x00,                          /* usIdentification. */
        0x00, 0x00,                          /* usFragmentOffset. */
        ipconfigUDP_TIME_TO_LIVE,            /* ucTimeToLive */
        ipPROTOCOL_UDP,                      /* ucProtocol. */
        0x00, 0x00,                          /* usHeaderChecksum. */
        0x00, 0x00, 0x00, 0x00               /* Source IP address. */
    }
};


const char * pcApplicationHostnameHook( void )
{
}
uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort )
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
void vApplicationIdleHook( void )
{
}
void vApplicationTickHook( void )
{
}
unsigned long ulGetRunTimeCounterValue( void )
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
