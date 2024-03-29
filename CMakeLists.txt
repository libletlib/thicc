#
#   ___       ___       ___       ___       ___
#  /\  \     /\__\     /\  \     /\  \     /\  \
#  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
#  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
# /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
# \/__/      /:/  /   \:\__\    \:\__\    \:\__\
#            \/__/     \/__/     \/__/     \/__/
#
# Copyright 2022 - 2023 Ville Rissanen
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1.   Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#
# 2.   Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.23)
enable_language(C)
project(thicc VERSION 0.0.1 DESCRIPTION "Write some thicc C." LANGUAGES C)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(SUPERPROJECT_NAME ${PROJECT_NAME})
set(SOURCE_DIRECTORY src)
set(HEADER_DIRECTORY include)
set(TEST_DIRECTORY test)
set(TEST_TIMEOUT 20)
set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/fortran)

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "-Weverything -pedantic-errors")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic-errors")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "/Tc /Za /Wall")
endif ()

file(GLOB_RECURSE THICC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "${SOURCE_DIRECTORY}/*.h")
file(GLOB_RECURSE THICC_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${SOURCE_DIRECTORY}/*.c")
file(GLOB_RECURSE TEST_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "${TEST_DIRECTORY}/*.h")
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${TEST_DIRECTORY}/*.c")

add_custom_target(npm_install ALL
        COMMAND npm install
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${THICC_HEADERS} ${THICC_SOURCES})
add_dependencies(${PROJECT_NAME} npm_install)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIRECTORY})
IF (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE m) # Link maths library
ENDIF ()
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER ${HEADER_DIRECTORY}/${PROJECT_NAME}.h)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

add_executable(${PROJECT_NAME}_test ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${HEADER_DIRECTORY})

add_executable(${PROJECT_NAME}_demo demo.c)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ${HEADER_DIRECTORY})

add_subdirectory(cpp)
if (NOT WIN32)
    #add_subdirectory(fortran)
    #add_subdirectory(objc)
endif ()

enable_testing()
add_test(NAME ${PROJECT_NAME}_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>)
set_tests_properties(${PROJECT_NAME}_test PROPERTIES TIMEOUT 20)
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})
