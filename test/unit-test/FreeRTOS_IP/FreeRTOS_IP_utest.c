/* Include Unity header */
#include "unity.h"

/* Include standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "mock_queue.h"
#include "mock_task.h"
#include "mock_semphr.h"

#include "mock_FreeRTOS_Sockets.h"
#include "mock_FreeRTOS_IP_Private.h"
#include "mock_FreeRTOS_ARP.h"
#include "mock_FreeRTOS_UDP_IP.h"
#include "mock_FreeRTOS_DHCP.h"
#include "mock_NetworkInterface.h"
#include "mock_NetworkBufferManagement.h"
#include "mock_FreeRTOS_DNS.h"
#include "mock_portable_functions.h"
#include "mock_FreeRTOS_IP_mock.h"

#include "FreeRTOS_IP.h"

#include "FreeRTOS_IP_stubs.c"
#include "catch_assert.h"

#include "FreeRTOSIPConfig.h"

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>

pthread_t thread1;
sem_t sem;

extern BaseType_t xIPTaskInitialised;
extern volatile BaseType_t xNetworkDownEventPending;
extern QueueHandle_t xNetworkEventQueue;
extern TaskHandle_t xIPTaskHandle;
extern IPTimer_t xTCPTimer;

const uint8_t ucIPAddress[ ipIP_ADDRESS_LENGTH_BYTES ];
const uint8_t ucNetMask[ ipIP_ADDRESS_LENGTH_BYTES ];
const uint8_t ucGatewayAddress[ ipIP_ADDRESS_LENGTH_BYTES ];
const uint8_t ucDNSServerAddress[ ipIP_ADDRESS_LENGTH_BYTES ];
const uint8_t ucMACAddress[ ipMAC_ADDRESS_LENGTH_BYTES ];


/* This stub is used to test the prvIPTask which cannot be accessed otherwise. */
static BaseType_t xTaskCreateStubLocal( TaskFunction_t pxTaskCode,
                                        const char * const pcName,
                                        const configSTACK_DEPTH_TYPE usStackDepth,
                                        void * const pvParameters,
                                        UBaseType_t uxPriority,
                                        TaskHandle_t * const pxCreatedTask,
                                        int callback )
{
    /* Call the IP task through posix threads */
    pthread_create( &thread1, NULL, pxTaskCode, NULL );
    pthread_join(thread1,NULL);

    return (BaseType_t)thread1;
}

static UBaseType_t EndFunctionStub( const QueueHandle_t xQueue,
                                    int callbacks )
{
    if( callbacks == 0 )
    {
        return 0;
    }
    else
    {
        pthread_exit( NULL );
        return 1;
    }
}

#define GET_THE_CONTROL_TO_LOOP_IN_PRV_IPTASK                          \
    /* Reset the variables as need be. */                              \
    xIPTaskInitialised = pdFALSE;                                      \
    xIPTaskHandle = NULL;                                              \
    xNetworkEventQueue = NULL;                                         \
                                                                       \
    /* Create the network event queue. */                              \
    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH,   \
                                         sizeof( IPStackEvent_t ),     \
                                         queueQUEUE_TYPE_BASE,         \
                                         &xNetworkEventQueueLocal );   \
                                                                       \
    /* Add the queue to registry. */                                   \
    vQueueAddToRegistry_Expect( &xNetworkEventQueueLocal, "NetEvnt" ); \
                                                                       \
    /* Make sure network buffers are initialised. */                   \
    xNetworkBuffersInitialise_ExpectAndReturn( pdPASS );               \
                                                                       \
    /* Init the network sockets. */                                    \
    vNetworkSocketsInit_Expect();                                      \
                                                                       \
    /* Create a thread which will execute the prvIPTask. */            \
    xTaskCreate_Stub( xTaskCreateStubLocal );                          \
                                                                       \
    /* This point onwards, all calls are from IP task. */              \
                                                                       \
    /****** FreeRTOS_NetworkDown calls *********/                      \
    /* Return any value, we don't care about this. */                  \
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );                 \
    xQueueGenericSend_ExpectAnyArgsAndReturn( pdPASS );                \
                                                                       \
    /********* prvIPTimerReload calls **********/                      \
    vTaskSetTimeOutState_ExpectAnyArgs();


void test_xIsCallingFromIPTask_Yes( void )
{
    BaseType_t xReturn;

    /* Initially that task handle is NULL. */
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );

    xReturn = xIsCallingFromIPTask();

    TEST_ASSERT_EQUAL( pdTRUE, xReturn );
}

void test_xIsCallingFromIPTask_No( void )
{
    BaseType_t xReturn;

    /* Initially that task handle is NULL. Return anything except NULL. */
    xTaskGetCurrentTaskHandle_ExpectAndReturn( ( struct tskTaskControlBlock * ) 1 );

    xReturn = xIsCallingFromIPTask();

    TEST_ASSERT_EQUAL( pdFALSE, xReturn );
}

void test_FreeRTOS_NetworkDown_IsCallingFromIPTask_MsgSendFail( void )
{
    BaseType_t xReturn;
    BaseType_t xSendReturn = pdFAIL;

    /* Initially that task handle is NULL. */
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );

    /* Failed to send a message. */
    xQueueGenericSend_ExpectAnyArgsAndReturn( xSendReturn );

    FreeRTOS_NetworkDown();

    /* Make sure that an event is seen as pending. */
    TEST_ASSERT_EQUAL( pdTRUE, xNetworkDownEventPending );
}

void test_FreeRTOS_NetworkDown_IsCallingFromIPTask_MsgSendSuccess( void )
{
    BaseType_t xReturn;
    BaseType_t xSendReturn = pdPASS;

    /* Initially that task handle is NULL. */
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );

    /* Failed to send a message. */
    xQueueGenericSend_ExpectAnyArgsAndReturn( xSendReturn );

    FreeRTOS_NetworkDown();

    /* Make sure that an event is not seen as pending. */
    TEST_ASSERT_EQUAL( pdFALSE, xNetworkDownEventPending );
}

void test_FreeRTOS_NetworkDown_IsNotCallingFromIPTask_MsgSendSuccess( void )
{
    BaseType_t xReturn;
    BaseType_t xSendReturn = pdPASS;

    /* Initially that task handle is NULL. Return anything except NULL. */
    xTaskGetCurrentTaskHandle_ExpectAndReturn( ( struct tskTaskControlBlock * ) 1 );

    /* Failed to send a message. */
    xQueueGenericSend_ExpectAnyArgsAndReturn( xSendReturn );

    FreeRTOS_NetworkDown();

    /* Make sure that an event is not seen as pending. */
    TEST_ASSERT_EQUAL( pdFALSE, xNetworkDownEventPending );
}

void test_FreeRTOS_NetworkDownFromISR_QueueSendFail( void )
{
    BaseType_t xReturn;
    BaseType_t HigherPriorityTaskWoken = pdFAIL;

    /* Ignore the address of two local variables. */
    xQueueGenericSendFromISR_ExpectAndReturn( xNetworkEventQueue, NULL, NULL, queueSEND_TO_BACK, HigherPriorityTaskWoken );
    xQueueGenericSendFromISR_IgnoreArg_pvItemToQueue();
    xQueueGenericSendFromISR_IgnoreArg_pxHigherPriorityTaskWoken();
    xQueueGenericSendFromISR_ReturnThruPtr_pxHigherPriorityTaskWoken( &HigherPriorityTaskWoken );

    xReturn = FreeRTOS_NetworkDownFromISR();

    TEST_ASSERT_EQUAL( HigherPriorityTaskWoken, xReturn );
    /* Make sure that an event is seen as pending. */
    TEST_ASSERT_EQUAL( pdTRUE, xNetworkDownEventPending );
}

void test_FreeRTOS_NetworkDownFromISR_QueueSendSuccess( void )
{
    BaseType_t xReturn;
    BaseType_t HigherPriorityTaskWoken = pdPASS;

    /* Ignore the address of two local variables. */
    xQueueGenericSendFromISR_ExpectAndReturn( xNetworkEventQueue, NULL, NULL, queueSEND_TO_BACK, HigherPriorityTaskWoken );
    xQueueGenericSendFromISR_IgnoreArg_pvItemToQueue();
    xQueueGenericSendFromISR_IgnoreArg_pxHigherPriorityTaskWoken();
    xQueueGenericSendFromISR_ReturnThruPtr_pxHigherPriorityTaskWoken( &HigherPriorityTaskWoken );

    xReturn = FreeRTOS_NetworkDownFromISR();

    TEST_ASSERT_EQUAL( HigherPriorityTaskWoken, xReturn );
    /* Make sure that an event is not seen as pending. */
    TEST_ASSERT_EQUAL( pdFALSE, xNetworkDownEventPending );
}

void test_FreeRTOS_GetUDPPayloadBuffer_ExcessBlockTime( void )
{
    const size_t uxRequestedSizeBytes = 100;
    const TickType_t uxBlockTimeTicks = ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS + 10;
    uint8_t pucEthernetBuffer[ sizeof( UDPPacket_t ) + uxRequestedSizeBytes ];
    void * pvReturn;

    NetworkBufferDescriptor_t xLocalNetworkBuffer;
    NetworkBufferDescriptor_t * pxNetworkBuffer = &( xLocalNetworkBuffer );

    pxNetworkBuffer->pucEthernetBuffer = pucEthernetBuffer;

    /* Expect moderated time ticks and return the network buffer. */
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn( sizeof( UDPPacket_t ) + uxRequestedSizeBytes, ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS, pxNetworkBuffer );

    pvReturn = FreeRTOS_GetUDPPayloadBuffer( uxRequestedSizeBytes, uxBlockTimeTicks );

    TEST_ASSERT_EQUAL( &( pucEthernetBuffer[ sizeof( UDPPacket_t ) ] ), pvReturn );
    TEST_ASSERT_EQUAL( sizeof( UDPPacket_t ) + uxRequestedSizeBytes, pxNetworkBuffer->xDataLength );
}

void test_FreeRTOS_GetUDPPayloadBuffer_ExcessBlockTime_GNWReturnsNULL( void )
{
    const size_t uxRequestedSizeBytes = 100;
    const TickType_t uxBlockTimeTicks = ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS + 10;
    void * pvReturn;

    /* Expect moderated time ticks  and return the network buffer. */
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn( sizeof( UDPPacket_t ) + uxRequestedSizeBytes, ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS, NULL );

    pvReturn = FreeRTOS_GetUDPPayloadBuffer( uxRequestedSizeBytes, uxBlockTimeTicks );

    TEST_ASSERT_EQUAL( NULL, pvReturn );
}

void test_FreeRTOS_GetUDPPayloadBuffer_ProperBlockTime( void )
{
    const size_t uxRequestedSizeBytes = 100;
    const TickType_t uxBlockTimeTicks = ipconfigUDP_MAX_SEND_BLOCK_TIME_TICKS - 10;
    uint8_t pucEthernetBuffer[ sizeof( UDPPacket_t ) + uxRequestedSizeBytes ];
    void * pvReturn;

    NetworkBufferDescriptor_t xLocalNetworkBuffer;
    NetworkBufferDescriptor_t * pxNetworkBuffer = &( xLocalNetworkBuffer );

    pxNetworkBuffer->pucEthernetBuffer = pucEthernetBuffer;

    /* Expect unmoderated time ticks and return the network buffer. */
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn( sizeof( UDPPacket_t ) + uxRequestedSizeBytes, uxBlockTimeTicks, pxNetworkBuffer );

    pvReturn = FreeRTOS_GetUDPPayloadBuffer( uxRequestedSizeBytes, uxBlockTimeTicks );

    TEST_ASSERT_EQUAL( &( pucEthernetBuffer[ sizeof( UDPPacket_t ) ] ), pvReturn );
    TEST_ASSERT_EQUAL( sizeof( UDPPacket_t ) + uxRequestedSizeBytes, pxNetworkBuffer->xDataLength );
}

void test_pxDuplicateNetworkBufferWithDescriptor_NewBufferNULL(void)
{
    NetworkBufferDescriptor_t xNetworkBuffer, * pxTestBuffer;
    size_t uxNewLength = 20;
    
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn(uxNewLength, 0, NULL);
    pxTestBuffer = pxDuplicateNetworkBufferWithDescriptor( &xNetworkBuffer,uxNewLength);
    
    TEST_ASSERT_EQUAL(NULL,pxTestBuffer);
}

void test_pxDuplicateNetworkBufferWithDescriptor(void)
{
    NetworkBufferDescriptor_t xNetworkBuffer, xNewBuffer, * pxTestBuffer;
    const size_t uxNewLength = 2000;
    
    uint8_t ucEthernetBuffer[1000], ucNewEthernetBuffer[uxNewLength];   
    memset(ucEthernetBuffer, 0xAB, sizeof(ucEthernetBuffer));
    memset(ucNewEthernetBuffer, 0, sizeof(ucNewEthernetBuffer));
    
    xNetworkBuffer.pucEthernetBuffer = ucEthernetBuffer;
    xNewBuffer.pucEthernetBuffer = ucNewEthernetBuffer;
    
    xNetworkBuffer.xDataLength = sizeof(ucEthernetBuffer);
    xNewBuffer.xDataLength = 0;
    
    xNetworkBuffer.ulIPAddress = 0xABCD1234;
    xNetworkBuffer.usPort = 0xAF;
    xNetworkBuffer.usBoundPort = 0xFA;
    
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn(uxNewLength, 0, &xNewBuffer);
    pxTestBuffer = pxDuplicateNetworkBufferWithDescriptor( &xNetworkBuffer,uxNewLength);
    
    TEST_ASSERT_EQUAL(&xNewBuffer,pxTestBuffer);
    TEST_ASSERT_EQUAL(xNewBuffer.xDataLength, uxNewLength);
    TEST_ASSERT_EQUAL(xNetworkBuffer.ulIPAddress,xNewBuffer.ulIPAddress);
    TEST_ASSERT_EQUAL(xNetworkBuffer.usPort,xNewBuffer.usPort);
    TEST_ASSERT_EQUAL(xNetworkBuffer.usBoundPort,xNewBuffer.usBoundPort);
    TEST_ASSERT_EQUAL_MEMORY( ucEthernetBuffer, ucNewEthernetBuffer, sizeof(ucEthernetBuffer) );
}

void test_pxDuplicateNetworkBufferWithDescriptor_SmallerLength(void)
{
    NetworkBufferDescriptor_t xNetworkBuffer, xNewBuffer, * pxTestBuffer;
    const size_t uxNewLength = 500;
    
    uint8_t ucEthernetBuffer[1000], ucNewEthernetBuffer[uxNewLength];   
    memset(ucEthernetBuffer, 0xAB, sizeof(ucEthernetBuffer));
    memset(ucNewEthernetBuffer, 0, sizeof(ucNewEthernetBuffer));
    
    xNetworkBuffer.pucEthernetBuffer = ucEthernetBuffer;
    xNewBuffer.pucEthernetBuffer = ucNewEthernetBuffer;
    
    xNetworkBuffer.xDataLength = sizeof(ucEthernetBuffer);
    xNewBuffer.xDataLength = 0;
    
    xNetworkBuffer.ulIPAddress = 0xABCD1234;
    xNetworkBuffer.usPort = 0xAF;
    xNetworkBuffer.usBoundPort = 0xFA;
    
    pxGetNetworkBufferWithDescriptor_ExpectAndReturn(uxNewLength, 0, &xNewBuffer);
    pxTestBuffer = pxDuplicateNetworkBufferWithDescriptor( &xNetworkBuffer,uxNewLength);
    
    TEST_ASSERT_EQUAL(&xNewBuffer,pxTestBuffer);
    TEST_ASSERT_EQUAL(xNewBuffer.xDataLength, uxNewLength);
    TEST_ASSERT_EQUAL(xNetworkBuffer.ulIPAddress,xNewBuffer.ulIPAddress);
    TEST_ASSERT_EQUAL(xNetworkBuffer.usPort,xNewBuffer.usPort);
    TEST_ASSERT_EQUAL(xNetworkBuffer.usBoundPort,xNewBuffer.usBoundPort);
    TEST_ASSERT_EQUAL_MEMORY( ucEthernetBuffer, ucNewEthernetBuffer, sizeof(ucNewEthernetBuffer) );
}

void test_pxUDPPayloadBuffer_to_NetworkBuffer_NULLInput(void)
{
    NetworkBufferDescriptor_t * pxResult;
    
    pxResult = pxUDPPayloadBuffer_to_NetworkBuffer(NULL);
    
    TEST_ASSERT_EQUAL(NULL, pxResult);    
}

void test_pxUDPPayloadBuffer_to_NetworkBuffer_UnallignedAccess(void)
{
    NetworkBufferDescriptor_t * pxResult;
    uintptr_t uxBuffer = ~0ULL;
    
    //uxBuffer += ( sizeof( UDPPacket_t ) + ipBUFFER_PADDING );
    
    pxResult = pxUDPPayloadBuffer_to_NetworkBuffer( (void *)uxBuffer );
    
    TEST_ASSERT_EQUAL(NULL, pxResult);
}


void test_pxUDPPayloadBuffer_to_NetworkBuffer_Happycase(void)
{
    NetworkBufferDescriptor_t * pxResult, xBuffer;
    
    uint8_t ucEthernetBuffer[1000];
    
    xBuffer.pucEthernetBuffer = ucEthernetBuffer;
    
    /* Add the network buffer details in the ethernet buffer. */
    *((NetworkBufferDescriptor_t **)xBuffer.pucEthernetBuffer) = &xBuffer;
    xBuffer.pucEthernetBuffer+=ipBUFFER_PADDING;
    
    pxResult = pxUDPPayloadBuffer_to_NetworkBuffer(&xBuffer.pucEthernetBuffer[sizeof( UDPPacket_t )]);
    
    TEST_ASSERT_EQUAL(&xBuffer, pxResult);    
}

void test_FreeRTOS_ReleaseUDPPayloadBuffer(void)
{
    vReleaseNetworkBufferAndDescriptor_Expect(NULL);
    FreeRTOS_ReleaseUDPPayloadBuffer(NULL);
}

void test_xSendEventStructToIPTask_IPTaskNotReady_NotNetworkDownEvent( void )
{
    IPStackEvent_t xEvent;
    TickType_t uxTimeouts;
    BaseType_t xReturn;
    
    xIPTaskInitialised = pdFALSE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = NULL;
    
    /* Anything except Network Down Event. */
    xEvent.eEventType = eNetworkDownEvent + 1;
    
    xReturn =xSendEventStructToIPTask( &xEvent, uxTimeouts );
    
    TEST_ASSERT_EQUAL(pdFAIL,xReturn);
}

void test_xSendEventStructToIPTask_IPTaskNotReady_NetworkDownEvent( void )
{
    IPStackEvent_t xEvent;
    TickType_t uxTimeouts = 100;
    BaseType_t xReturn;
    
    xIPTaskInitialised = pdFALSE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = NULL;
    
    /* Network Down Event. */
    xEvent.eEventType = eNetworkDownEvent;
    
    xTaskGetCurrentTaskHandle_ExpectAndReturn( xIPTaskHandle );
    
    /* Expect the timeout to be zero since we are calling from IP task. */
    xQueueGenericSend_ExpectAndReturn( xNetworkEventQueue, &xEvent, 0, queueSEND_TO_BACK, pdFAIL );
    
    xReturn =xSendEventStructToIPTask( &xEvent, uxTimeouts );
    
    TEST_ASSERT_EQUAL(pdFAIL,xReturn);
}

void test_xSendEventStructToIPTask_IPTaskReady_TCPTimerEvent_NoMsgs( void )
{
    IPStackEvent_t xEvent;
    TickType_t uxTimeouts = 100;
    BaseType_t xReturn;
    
    xIPTaskInitialised = pdTRUE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = (void*) 0x1234;;
    
    /* This should be set later in the code. */
    xTCPTimer.bExpired = pdFALSE_UNSIGNED;
    
    /* TCP timer event. */
    xEvent.eEventType = eTCPTimerEvent;
    
    /* No messages waiting. */
    uxQueueMessagesWaiting_ExpectAndReturn(xNetworkEventQueue, 0 );
    
    xTaskGetCurrentTaskHandle_ExpectAndReturn( xIPTaskHandle );
    
    /* Expect the timeout to be zero since we are calling from IP task. */
    xQueueGenericSend_ExpectAndReturn( xNetworkEventQueue, &xEvent, 0, queueSEND_TO_BACK, pdFAIL );
    
    xReturn =xSendEventStructToIPTask( &xEvent, uxTimeouts );
    
    TEST_ASSERT_EQUAL(pdFAIL,xReturn);
}

void test_xSendEventStructToIPTask_IPTaskReady_TCPTimerEvent_NonZeroMsgs( void )
{
    IPStackEvent_t xEvent;
    TickType_t uxTimeouts = 100;
    BaseType_t xReturn;
    
    xIPTaskInitialised = pdTRUE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = (void*) 0x1234;;
    
    /* This should be set later in the code. */
    xTCPTimer.bExpired = pdFALSE_UNSIGNED;
    
    /* TCP timer event. */
    xEvent.eEventType = eTCPTimerEvent;
    
    /* Non zero messages waiting. */
    uxQueueMessagesWaiting_ExpectAndReturn(xNetworkEventQueue, 1 );
    
    xReturn =xSendEventStructToIPTask( &xEvent, uxTimeouts );
    
    TEST_ASSERT_EQUAL(pdPASS,xReturn);
}

void test_FreeRTOS_IPInit_CallingSecondTime( void )
{
    xIPTaskInitialised = pdTRUE;

    catch_assert( FreeRTOS_IPInit( ucIPAddress,
                                   ucNetMask,
                                   ucGatewayAddress,
                                   ucDNSServerAddress,
                                   ucMACAddress ) );
}

void test_FreeRTOS_IPInit_NetworkQInit( void )
{
    xIPTaskInitialised = pdFALSE;
    /* Any non-NULL value. */
    xNetworkEventQueue = ( void * ) 0x1234;

    catch_assert( FreeRTOS_IPInit( ucIPAddress,
                                   ucNetMask,
                                   ucGatewayAddress,
                                   ucDNSServerAddress,
                                   ucMACAddress ) );
}

void test_FreeRTOS_IPInit_IPTaskInit( void )
{
    xIPTaskInitialised = pdFALSE;
    xNetworkEventQueue = NULL;
    /* Any non-NULL value. */
    xIPTaskHandle = ( void * ) 0x1234;

    catch_assert( FreeRTOS_IPInit( ucIPAddress,
                                   ucNetMask,
                                   ucGatewayAddress,
                                   ucDNSServerAddress,
                                   ucMACAddress ) );
}

void test_FreeRTOS_IPInit_EventQueueCannotBeCreated( void )
{
    xIPTaskInitialised = pdFALSE;
    xNetworkEventQueue = NULL;
    xIPTaskHandle = NULL;

    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH, sizeof( IPStackEvent_t ), queueQUEUE_TYPE_BASE, NULL );

    catch_assert( FreeRTOS_IPInit( ucIPAddress,
                                   ucNetMask,
                                   ucGatewayAddress,
                                   ucDNSServerAddress,
                                   ucMACAddress ) );
}

void test_FreeRTOS_IPInit_BuffersInitFail( void )
{
    BaseType_t xReturn;

    struct QueueDefinition xNetworkEventQueueLocal;

    xIPTaskInitialised = pdFALSE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = NULL;

    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH, sizeof( IPStackEvent_t ), queueQUEUE_TYPE_BASE, &xNetworkEventQueueLocal );

    vQueueAddToRegistry_Expect( &xNetworkEventQueueLocal, "NetEvnt" );

    xNetworkBuffersInitialise_ExpectAndReturn( pdFAIL );

    vQueueDelete_Expect( &xNetworkEventQueueLocal );

    xReturn = FreeRTOS_IPInit( ucIPAddress,
                               ucNetMask,
                               ucGatewayAddress,
                               ucDNSServerAddress,
                               ucMACAddress );

    TEST_ASSERT_EQUAL( pdFALSE, xReturn );
}

void test_FreeRTOS_IPInit_FullSuccess( void )
{
    BaseType_t xReturn;

    struct QueueDefinition xNetworkEventQueueLocal;

    xIPTaskInitialised = pdFALSE;
    xIPTaskHandle = NULL;
    xNetworkEventQueue = NULL;

    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH, sizeof( IPStackEvent_t ), queueQUEUE_TYPE_BASE, &xNetworkEventQueueLocal );

    vQueueAddToRegistry_Expect( &xNetworkEventQueueLocal, "NetEvnt" );

    xNetworkBuffersInitialise_ExpectAndReturn( pdPASS );

    vNetworkSocketsInit_Expect();

    xTaskCreate_ExpectAnyArgsAndReturn( pdTRUE );

    xReturn = FreeRTOS_IPInit( ucIPAddress,
                               ucNetMask,
                               ucGatewayAddress,
                               ucDNSServerAddress,
                               ucMACAddress );

    TEST_ASSERT_EQUAL( pdTRUE, xReturn );
    TEST_ASSERT_EQUAL( 0, *ipLOCAL_IP_ADDRESS_POINTER );
}

void test_FreeRTOS_IPInit_EmptyQueue( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;

    GET_THE_CONTROL_TO_LOOP_IN_PRV_IPTASK;

    /***** prvCheckNetworkTimers *****/

    /* This stub will return 0 at first but later will be used to exit
     * out of the prvIPTask which is an infinite loop. */
    uxQueueMessagesWaiting_Stub( EndFunctionStub );
    {
        /**** prvIPTimerCheck ****/
        xTaskCheckForTimeOut_ExpectAnyArgsAndReturn( pdTRUE );
        {
            /***** prvIPTimerStart *****/
            vTaskSetTimeOutState_ExpectAnyArgs();
        }
    }
    /**** xTCPTimerCheck ****/
    xTCPTimerCheck_ExpectAnyArgsAndReturn( 0 );
    /***** prvIPTimerStart *****/
    vTaskSetTimeOutState_ExpectAnyArgs();


    xQueueReceive_ExpectAnyArgsAndReturn( pdFALSE );

    /* Call the function under test. In this case, the function we
     * are testing is the IP task. */
    FreeRTOS_IPInit( ucIPAddress,
                     ucNetMask,
                     ucGatewayAddress,
                     ucDNSServerAddress,
                     ucMACAddress );
}



void test_prvIPTask_EmptyQueue_NWDownEventPending_NetInItSuccesss( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;
                                                                       
    /* Reset the variables as need be. */                              
    xIPTaskInitialised = pdFALSE;                                      
    xIPTaskHandle = NULL;                                              
    xNetworkEventQueue = NULL;                                         
                                                                       
    /* Create the network event queue. */                              
    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH,   
                                         sizeof( IPStackEvent_t ),     
                                         queueQUEUE_TYPE_BASE,         
                                         &xNetworkEventQueueLocal );   
                                                                       
    /* Add the queue to registry. */                                   
    vQueueAddToRegistry_Expect( &xNetworkEventQueueLocal, "NetEvnt" ); 
                                                                       
    /* Make sure network buffers are initialised. */                   
    xNetworkBuffersInitialise_ExpectAndReturn( pdPASS );               
                                                                       
    /* Init the network sockets. */                                    
    vNetworkSocketsInit_Expect();                                      
                                                                       
    /* Create a thread which will execute the prvIPTask. */            
    xTaskCreate_Stub( xTaskCreateStubLocal );                          
                                                                       
    /* This point onwards, all calls are from IP task. */              
                                                                       
    /****** FreeRTOS_NetworkDown calls *********/                      
    /* Return any value, we don't care about this. */                  
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );                 
    xQueueGenericSend_ExpectAnyArgsAndReturn( pdFAIL );                
                                                                       
    /********* prvIPTimerReload calls **********/                      
    vTaskSetTimeOutState_ExpectAnyArgs();

    /***** prvCheckNetworkTimers *****/

    /* This stub will return 0 at first but later will be used to exit
     * out of the prvIPTask which is an infinite loop. */
    uxQueueMessagesWaiting_Stub( EndFunctionStub );
    {
        /**** prvIPTimerCheck ****/
        xTaskCheckForTimeOut_ExpectAnyArgsAndReturn( pdTRUE );
        {
            /***** prvIPTimerStart *****/
            vTaskSetTimeOutState_ExpectAnyArgs();
        }
    }
    /**** xTCPTimerCheck ****/
    xTCPTimerCheck_ExpectAnyArgsAndReturn( 0 );
    /***** prvIPTimerStart *****/
    vTaskSetTimeOutState_ExpectAnyArgs();


    xQueueReceive_ExpectAnyArgsAndReturn( pdFALSE );
    
    FreeRTOS_ClearARP_Expect();
    
    /* Make sure that this succeeds. */
    xNetworkInterfaceInitialise_ExpectAndReturn(pdPASS);
    
    vDHCPProcess_Expect( pdTRUE, eInitialWait );

    /* Call the function under test. In this case, the function we
     * are testing is the IP task. */
    FreeRTOS_IPInit( ucIPAddress,
                     ucNetMask,
                     ucGatewayAddress,
                     ucDNSServerAddress,
                     ucMACAddress );
}

void test_prvIPTask_EmptyQueue_NWDownEventPending_NetInItFail( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;                                           
                                                                       
    /* Reset the variables as need be. */                              
    xIPTaskInitialised = pdFALSE;                                      
    xIPTaskHandle = NULL;                                              
    xNetworkEventQueue = NULL;                                         
                                                                       
    /* Create the network event queue. */                              
    xQueueGenericCreate_ExpectAndReturn( ipconfigEVENT_QUEUE_LENGTH,   
                                         sizeof( IPStackEvent_t ),     
                                         queueQUEUE_TYPE_BASE,         
                                         &xNetworkEventQueueLocal );   
                                                                       
    /* Add the queue to registry. */                                   
    vQueueAddToRegistry_Expect( &xNetworkEventQueueLocal, "NetEvnt" ); 
                                                                       
    /* Make sure network buffers are initialised. */                   
    xNetworkBuffersInitialise_ExpectAndReturn( pdPASS );               
                                                                       
    /* Init the network sockets. */                                    
    vNetworkSocketsInit_Expect();                                      
                                                                       
    /* Create a thread which will execute the prvIPTask. */            
    xTaskCreate_Stub( xTaskCreateStubLocal );                          
                                                                       
    /* This point onwards, all calls are from IP task. */              
                                                                       
    /****** FreeRTOS_NetworkDown calls *********/                      
    /* Return any value, we don't care about this. */                  
    xTaskGetCurrentTaskHandle_ExpectAndReturn( NULL );                 
    xQueueGenericSend_ExpectAnyArgsAndReturn( pdFAIL );                
                                                                       
    /********* prvIPTimerReload calls **********/                      
    vTaskSetTimeOutState_ExpectAnyArgs();

    /***** prvCheckNetworkTimers *****/

    /* This stub will return 0 at first but later will be used to exit
     * out of the prvIPTask which is an infinite loop. */
    uxQueueMessagesWaiting_Stub( EndFunctionStub );
    {
        /**** prvIPTimerCheck ****/
        xTaskCheckForTimeOut_ExpectAnyArgsAndReturn( pdTRUE );
        {
            /***** prvIPTimerStart *****/
            vTaskSetTimeOutState_ExpectAnyArgs();
        }
    }
    /**** xTCPTimerCheck ****/
    xTCPTimerCheck_ExpectAnyArgsAndReturn( 0 );
    /***** prvIPTimerStart *****/
    vTaskSetTimeOutState_ExpectAnyArgs();


    xQueueReceive_ExpectAnyArgsAndReturn( pdFALSE );
    
    /**** prvProcessNetworkDownEvent ****/
    /* Since this is the second time, application hook will be called. */
    vApplicationIPNetworkEventHook_Expect( eNetworkDown );    
    FreeRTOS_ClearARP_Expect();
    
    /* Make sure that this fails. */
    xNetworkInterfaceInitialise_ExpectAndReturn(pdFAIL);
    
    vTaskDelay_Expect(pdMS_TO_TICKS(3000));
    
    /****** FreeRTOS_NetworkDown calls ******/
    xTaskGetCurrentTaskHandle_ExpectAndReturn(NULL);
    xQueueGenericSend_ExpectAnyArgsAndReturn( pdFAIL );

    /* Call the function under test. In this case, the function we
     * are testing is the IP task. */
    FreeRTOS_IPInit( ucIPAddress,
                     ucNetMask,
                     ucGatewayAddress,
                     ucDNSServerAddress,
                     ucMACAddress );
}

void test_FreeRTOS_GetAddressConfiguration_AllNULLs(void)
{
    FreeRTOS_GetAddressConfiguration(NULL,NULL,NULL,NULL);
}

void test_FreeRTOS_GetAddressConfiguration_NoNULLs(void)
{
    uint32_t ulIPAddress,ulNetMask, ulGatewayAddress, ulDNSServerAddress;
    
    FreeRTOS_GetAddressConfiguration(&ulIPAddress,&ulNetMask, &ulGatewayAddress, &ulDNSServerAddress);
    TEST_ASSERT_EQUAL(*ipLOCAL_IP_ADDRESS_POINTER,ulIPAddress);
    TEST_ASSERT_EQUAL(xNetworkAddressing.ulNetMask, ulNetMask);
    TEST_ASSERT_EQUAL(xNetworkAddressing.ulGatewayAddress,ulGatewayAddress);
    TEST_ASSERT_EQUAL(xNetworkAddressing.ulDNSServerAddress,ulDNSServerAddress);
}

void test_FreeRTOS_SetAddressConfiguration_AllNULLs(void)
{
    FreeRTOS_SetAddressConfiguration(NULL,NULL,NULL,NULL);
}

void test_FreeRTOS_SetAddressConfiguration_NoNULLs(void)
{
    uint32_t ulIPAddress = 0xABCD1234,ulNetMask=0xABCD5678, ulGatewayAddress=0xEFAB1234, ulDNSServerAddress=0x3456ABFE;
    
    FreeRTOS_SetAddressConfiguration(&ulIPAddress,&ulNetMask, &ulGatewayAddress, &ulDNSServerAddress);
    TEST_ASSERT_EQUAL(ulIPAddress,*ipLOCAL_IP_ADDRESS_POINTER);
    TEST_ASSERT_EQUAL(ulNetMask,xNetworkAddressing.ulNetMask);
    TEST_ASSERT_EQUAL(ulGatewayAddress,xNetworkAddressing.ulGatewayAddress);
    TEST_ASSERT_EQUAL(ulDNSServerAddress,xNetworkAddressing.ulDNSServerAddress);
}

void test_FreeRTOS_SendPingRequest_NotEnoughNetworkBuffers(void)
{
    uint32_t ulIPAddress;
    size_t uxNumberOfBytesToSend = 0;
    TickType_t uxBlockTimeTicks;
    BaseType_t xResult;
    
    uxGetNumberOfFreeNetworkBuffers_ExpectAndReturn(2);
    
    xResult = FreeRTOS_SendPingRequest(ulIPAddress, uxNumberOfBytesToSend, uxBlockTimeTicks);
    TEST_ASSERT_EQUAL(pdFAIL,xResult);
}









































