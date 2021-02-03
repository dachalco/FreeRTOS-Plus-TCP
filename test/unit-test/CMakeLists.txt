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

# ====================  Define your project name (edit) ========================
set( project_name "FreeRTOS_TCP" )

# =====================  Create your mock here  (edit)  ========================
# ================= Create the library under test here (edit) ==================

# Base name for temporary files
set( TEMP_BASE ${CMAKE_BINARY_DIR}/${project_name} )

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
    execute_process( COMMAND sed -E "s/static/     /g"
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                     INPUT_FILE ${file}
                     OUTPUT_FILE ${ANNEXED_DIR}/${Modified_file}_annexed.c )
endforeach()
