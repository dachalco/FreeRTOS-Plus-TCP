cmake_minimum_required ( VERSION 3.13.0 )
project ( "FreeRTOS-Plus-TCP test"
          VERSION 1.0.0
          LANGUAGES C )

# Allow the project to be organized into folders.
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# Use C90.
set( CMAKE_C_STANDARD 90 )
set( CMAKE_C_STANDARD_REQUIRED ON )

# Do not allow in-source build.
if( ${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR} )
    message( FATAL_ERROR "In-source build is not allowed. Please build in a separate directory, such as ${PROJECT_SOURCE_DIR}/build." )
endif()

# =============  Define source path and related variables (edit)  ==============
# Set global path variables.
get_filename_component(__MODULE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set( MODULE_ROOT_DIR ${__MODULE_ROOT_DIR} CACHE INTERNAL "FreeRTOS-Plus-TCP repository root." )

# Include filepaths for source and include.
include( ${MODULE_ROOT_DIR}/test/unit-test/TCPFilePaths.cmake )

set( UNITY_DIR ${MODULE_ROOT_DIR}/tools/CMock/vendor/unity )

# ====================  Define your project name (edit) ========================
set( project_name "FreeRTOS_TCP" )

# =====================  Create your mock here  (edit)  ========================

# ================= Create the library under test here (edit) ==================

# Base directories for temporary files
set( ANNEXED_DIR ${CMAKE_BINARY_DIR}/${project_name}_Annexed )

# Create the directory
execute_process( COMMAND mkdir ${ANNEXED_DIR} )

# Copy all files into one.
foreach( file ${TCP_SOURCES} )

    # Get all static function declarations in a header file (See the shell script)
    execute_process( COMMAND /bin/sh ${CMAKE_BINARY_DIR}/../create_header.sh ${file} ${ANNEXED_DIR}/${project_name}_annex.h
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )

    # Get only the filename without the extension and the path
    get_filename_component( Modified_file ${file} NAME_WLE )

    # Remove "static" from the file and put it in a temporary
    # file with modified name
    execute_process( COMMAND sed -E "/static portINLINE ipDECL_CAST_/! s/[_]?static/     /g"
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                     INPUT_FILE ${file}
                     OUTPUT_FILE ${ANNEXED_DIR}/${Modified_file}_annexed.c )
endforeach()

# Add the annexed directory to the include directory
list( APPEND TCP_INCLUDE_DIRS
             ${ANNEXED_DIR} )

# Add the annexed sources to a list
file( GLOB TCP_ANNEXED_SOURCES
           ${ANNEXED_DIR}/*.c )

# Add kernel sources to a list
file( GLOB KERNEL_SOURCES
           ${MODULE_ROOT_DIR}/test/FreeRTOS-Kernel/*.c )

include( ${MODULE_ROOT_DIR}/test/unit-test/cmock_build.cmake )

# Check if the Unity source directory exists.
if( NOT EXISTS ${UNITY_DIR}/src )
    message( FATAL_ERROR "Unity cannot be found in ${UNITY_DIR}. Was it submoduled?" )
endif()

# Use CTest utility for managing test runs. This has to be added BEFORE
# defining test targets with add_test()
enable_testing()

# Add build targets for Unity and Unit, required for unit testing.
#add_unity_targets()

# Add function to enable Unity based tests and coverage.
include( ${MODULE_ROOT_DIR}/test/unit-test/cmock/create_test.cmake )

# Add kernel sources to a list
file( GLOB KERNEL_INCLUDES
           ${MODULE_ROOT_DIR}/test/FreeRTOS-Kernel/include/*.h )

# Copy all files into one.
foreach( file ${KERNEL_INCLUDES} )

    get_filename_component( Modified_file ${file} NAME_WLE )

    # Remove "static" from the file and put it in a temporary
    # file with modified name
    execute_process( COMMAND sed "s/PRIVILEGED_FUNCTION//g;s/portDONT_DISCARD//g"
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                     INPUT_FILE ${file}
                     OUTPUT_FILE ${ANNEXED_DIR}/${Modified_file}_annexed.h )
endforeach()

set( KERNEL_INCLUDE_DIRS ${ANNEXED_DIR} )
#${MODULE_ROOT_DIR}/test/FreeRTOS-Kernel/include )
#PRIVILEGED_FUNCTION

list( APPEND real_include_dirs
             ${TCP_INCLUDE_DIRS}
             ${KERNEL_INCLUDE_DIRS}
             ${MODULE_ROOT_DIR}/test/FreeRTOS-Kernel/include
             ${MODULE_ROOT_DIR}/test/unit-test/ConfigFiles )

# =============================  (end edit)  ===================================
set( real_name "${project_name}_real" )

set(CMOCK_DIR ${MODULE_ROOT_DIR}/tools/CMock)

# Add build targets for CMock and Unit, required for unit testing.
add_cmock_targets()

include(${MODULE_ROOT_DIR}/test/unit-test/ModuleCmake/IP_c_buld.cmake)
create_ip_c_utest(FreeRTOS_IP)

# Add a target for running coverage on tests.
add_custom_target( coverage
    COMMAND ${CMAKE_COMMAND} -DUNITY_DIR=${UNITY_DIR}
    -P ${MODULE_ROOT_DIR}/test/unit-test/cmock/coverage.cmake
    DEPENDS unity FreeRTOS_IP_utest
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
