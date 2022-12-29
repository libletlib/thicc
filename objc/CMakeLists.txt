cmake_minimum_required(VERSION 3.23)
enable_language(OBJC)
project(thicc_objc VERSION 0.0.1 DESCRIPTION "Write some thicc Objective-C." LANGUAGES OBJC)

set(CMAKE_OBJC_STANDARD 90)
set(CMAKE_OBJC_EXTENSIONS OFF)
set(CMAKE_OBJC_STANDARD_REQUIRED ON)

file(GLOB_RECURSE THICC_OBJC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/objc "${SOURCE_DIRECTORY}/*.h")
file(GLOB_RECURSE THICC_OBJC_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/objc "${SOURCE_DIRECTORY}/*.m")

add_library(${PROJECT_NAME} ${THICC_OBJC_HEADERS} ${THICC_OBJC_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUPERPROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})

add_executable(${PROJECT_NAME}_demo demo.m)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ${HEADER_DIRECTORY})

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})