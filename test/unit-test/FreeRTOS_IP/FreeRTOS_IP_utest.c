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
    
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 100;
    
    /* Wait for a max timeout of 5 seconds. If not finished in
     * that time, then the test will fail. */
    int s;
    while((s = sem_timedwait( &sem, &ts ))==-1 && errno == EINTR )
    {
        continue;
    }
    
    if( s == -1 )
    {    
        pthread_cancel(thread1);
    }
    
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
        sem_post( &sem );
        pthread_exit( NULL );
    }
}

static void initSemaphore( void )
{
    static int init = 0;

    if( !init )
    {
        sem_init( &sem, 0, 0 );
        init = 1;
    }
}

#define GET_THE_CONTROL_TO_LOOP_IN_PRV_IPTASK                          \
    /* Initialise the semaphore if not already done. */                \
    initSemaphore();                                                   \
                                                                       \
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



void test_prvIPTask_EmptyQueue_NWDownEventPending_NetInItFail( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;
#if 0
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 5;

#endif

    /* Initialise the semaphore if not already done. */                
    initSemaphore();                                                   
                                                                       
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
    
    /* Make sure that this fails. */
    xNetworkInterfaceInitialise_ExpectAndReturn(pdFAIL);
    
    vTaskDelay_Expect(pdMS_TO_TICKS(3000));
    xTaskGetCurrentTaskHandle_ExpectAndReturn(NULL);

    /* Call the function under test. In this case, the function we
     * are testing is the IP task. */
    FreeRTOS_IPInit( ucIPAddress,
                     ucNetMask,
                     ucGatewayAddress,
                     ucDNSServerAddress,
                     ucMACAddress );

#if 0
    /* Wait for a max timeout of 5 seconds. If not finished in
     * that time, then the test will fail. */
    int s;
    while((s = sem_timedwait( &sem, &ts ))==-1 && errno == EINTR )
    {
        continue;
    }
    
    if( s == -1 )
    {    
        pthread_cancel(thread1);
    }
    #endif
}


void test_prvIPTask_EmptyQueue_NWDownEventPending_NetInItSuccesss( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;

    struct timespec ts;

    ts.tv_sec = 5;

    /* Initialise the semaphore if not already done. */                
    initSemaphore();                                                   
                                                                       
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


    /* Wait for a max timeout of 5 seconds. If not finished in
     * that time, then the test will fail. */
//    sem_timedwait( &sem, &ts );
}

void test_FreeRTOS_IPInit_EmptyQueue( void )
{
    struct QueueDefinition xNetworkEventQueueLocal;

    struct timespec ts;

    ts.tv_sec = 5;

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


    /* Wait for a max timeout of 5 seconds. If not finished in
     * that time, then the test will fail. */
    sem_timedwait( &sem, &ts );
}

