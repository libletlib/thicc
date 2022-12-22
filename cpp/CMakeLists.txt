cmake_minimum_required(VERSION 3.23)
enable_language(CXX)
project(thicc_cpp VERSION 0.0.1 DESCRIPTION "Write some thicc C++." LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_demo demo.cpp)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${SUPERPROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ../include include)

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT 20)