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
enable_language(CXX)
project(thicc_cpp VERSION 0.0.1 DESCRIPTION "Write some thicc C++." LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if (APPLE)
        set(CMAKE_CXX_FLAGS "-Weverything -pedantic-errors")
    else ()
        set(CMAKE_CXX_FLAGS "-Weverything -pedantic-errors")
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic-errors")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/Wall /Zc:__cplusplus /EHsc")
endif ()

add_executable(${PROJECT_NAME}_demo demo.cpp)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${SUPERPROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})
