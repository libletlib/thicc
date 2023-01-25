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
enable_language(OBJC)
project(thicc_objc VERSION 0.0.1 DESCRIPTION "Write some thicc Objective-C." LANGUAGES OBJC)

set(CMAKE_OBJC_STANDARD 90)
set(CMAKE_OBJC_EXTENSIONS OFF)
set(CMAKE_OBJC_STANDARD_REQUIRED ON)

file(GLOB_RECURSE THICC_OBJC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/objc "${SOURCE_DIRECTORY}/*.h")
file(GLOB_RECURSE THICC_OBJC_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/objc "${SOURCE_DIRECTORY}/*.m")

add_library(${PROJECT_NAME} STATIC ${THICC_OBJC_HEADERS} ${THICC_OBJC_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUPERPROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})

add_executable(${PROJECT_NAME}_demo demo.m)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})
