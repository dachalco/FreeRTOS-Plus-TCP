/* Include Unity header */
#include <unity.h>

/* Include standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"

/* Include header file(s) which have declaration
 * of functions under test */
#include "FreeRTOSIPConfig.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_ARP.h"
#include "FreeRTOS_DNS.h"

/* Include the mocked header files. */
#include "mock_FreeRTOS_Sockets.h"
#include "mock_FreeRTOS_ARP.h"
#include "mock_FreeRTOS_UDP_IP.h"
#include "mock_FreeRTOS_DHCP.h"
#include "mock_NetworkInterface.h"
#include "mock_FreeRTOS_DNS.h"
#include "mock_queue_annexed.h"
#include "mock_NetworkBufferManagement.h"
#include "mock_task_annexed.h"

#include "/home/ubuntu/Desktop/CMockunittest/test/unit-test/build/FreeRTOS_TCP_Annexed/FreeRTOS_TCP_annex.h"

void test_pxGetNetworkBufferWithDescriptor( void )
{
    void * temp;

    UBaseType_t uxRequestedSizeBytes = 400;
    NetworkBufferDescriptor_t xReturn, *pointerReturn = &xReturn;
    TickType_t xTimeout = 100;
    void * pvResult;

    xReturn.pucEthernetBuffer = malloc( sizeof( UDPPacket_t ) + uxRequestedSizeBytes );

    pxGetNetworkBufferWithDescriptor_ExpectAndReturn( uxRequestedSizeBytes + sizeof( UDPPacket_t ),
                                                      xTimeout,
                                                      pointerReturn );

    pvResult = FreeRTOS_GetUDPPayloadBuffer( uxRequestedSizeBytes, xTimeout );

    TEST_ASSERT_NOT_EQUAL( pvResult, NULL );


    pxGetNetworkBufferWithDescriptor_ExpectAndReturn( uxRequestedSizeBytes + sizeof( UDPPacket_t ),
                                                      xTimeout,
                                                      NULL );

    pvResult = FreeRTOS_GetUDPPayloadBuffer( uxRequestedSizeBytes, xTimeout );

    TEST_ASSERT_EQUAL( pvResult, NULL );
}

#define DEF_ADDR_VALS 0x1234

void test_FreeRTOS_GetAddressConfiguration( void )
{
    uint32_t ulIPAddress = DEF_ADDR_VALS;
    uint32_t ulNetMask = DEF_ADDR_VALS;
    uint32_t ulGatewayAddress = DEF_ADDR_VALS;
    uint32_t ulDNSServerAddress = DEF_ADDR_VALS;

    FreeRTOS_GetAddressConfiguration( NULL, NULL, NULL, NULL );
    TEST_ASSERT_EQUAL( ulIPAddress, DEF_ADDR_VALS );
    TEST_ASSERT_EQUAL( ulNetMask, DEF_ADDR_VALS );
    TEST_ASSERT_EQUAL( ulGatewayAddress, DEF_ADDR_VALS );
    TEST_ASSERT_EQUAL( ulDNSServerAddress, DEF_ADDR_VALS );

    FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
    TEST_ASSERT_EQUAL( ulIPAddress, 0 );
    TEST_ASSERT_EQUAL( ulNetMask, 0 );
    TEST_ASSERT_EQUAL( ulGatewayAddress, 0 );
    TEST_ASSERT_EQUAL( ulDNSServerAddress, 0 );
}

void test_prvProcessNetworkDownEvent( void )
{
    vTaskDelay_Ignore();
    xTaskGetCurrentTaskHandle_IgnoreAndReturn( NULL );
    xQueueGenericSend_IgnoreAndReturn(pdPASS);

    prvProcessNetworkDownEvent();
}
