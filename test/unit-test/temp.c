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


