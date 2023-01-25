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
