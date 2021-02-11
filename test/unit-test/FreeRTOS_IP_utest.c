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

/* Include the mocked header files. */
#include "mock_NetworkBufferManagement.h"

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

void test_FreeRTOS_GetAddressConfiguration( void )
{

}
