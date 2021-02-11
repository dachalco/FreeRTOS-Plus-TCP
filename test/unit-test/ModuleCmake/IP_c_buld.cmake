# This file is used to define the mocks and tests used for IP.c source file
set(utest_module_name "FreeRTOS_IP")

function(create_ip_c_utest target)
    # List the files required for the build
    list( APPEND real_source_dirs
             ${TCP_ANNEXED_SOURCES}
             ${KERNEL_SOURCES}
             ${MODULE_ROOT_DIR}/test/unit-test/stubs/FreeRTOS_ARP_stubs.c )

    # list the files to mock here
    list(APPEND ${target}_mock_list
                "${MODULE_ROOT_DIR}/include/FreeRTOS_Sockets.h"
                "${MODULE_ROOT_DIR}/include/FreeRTOS_ARP.h"
                "${MODULE_ROOT_DIR}/include/FreeRTOS_UDP_IP.h"
                "${MODULE_ROOT_DIR}/include/FreeRTOS_DHCP.h"
                "${MODULE_ROOT_DIR}/include/NetworkInterface.h"
                "${MODULE_ROOT_DIR}/include/NetworkBufferManagement.h"
                "${MODULE_ROOT_DIR}/include/FreeRTOS_DNS.h"
            )

    # list the directories your mocks need
    list(APPEND ${target}_mock_include_list
                .
                ${MODULE_ROOT_DIR}/test/unit-test/ConfigFiles
                ${KERNEL_INCLUDE_DIRS}
                ${MODULE_ROOT_DIR}/include
                ${MODULE_ROOT_DIR}/tools/CMock/src
                ${MODULE_ROOT_DIR}/tools/CMock/vendor/unity/src
            )

    #list the definitions of your mocks to control what to be included
    list(APPEND ${target}_mock_define_list
                ""
           )

    set( mock_name ${utest_module_name} )

    create_mock_list(${mock_name}
                "${${target}_mock_list}"
                "${MODULE_ROOT_DIR}/test/unit-test/cmock/project.yml"
                "${${target}_mock_include_list}"
                "${${target}_mock_define_list}"
        )

    set( ${target}_real_name "${project_name}_real" )

    create_real_library( ${${target}_real_name}
                         "${real_source_dirs}"
                         "${real_include_dirs}"
                         ${mock_name}
            )

    list(APPEND utest_link_list
                lib${${target}_real_name}.a
                -lcmock
                -lunity
            )

    list(APPEND utest_dep_list
                ${${target}_real_name}
                -l${mock_name}
            )

    set(utest_name "${utest_module_name}_utest")
    set(utest_source "${utest_module_name}_utest.c")

    list(APPEND test_include_directories
                ${MODULE_ROOT_DIR}/test/unit-test/ConfigFiles
                ${KERNEL_INCLUDE_DIRS}
                ${MODULE_ROOT_DIR}/include)

    create_test(${utest_name}
                ${utest_source}
                "${utest_link_list}"
                "${utest_dep_list}"
                "${test_include_directories}"
            )

endfunction()

