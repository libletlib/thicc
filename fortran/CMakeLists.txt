cmake_minimum_required(VERSION 3.23)
enable_language(Fortran)
project(thicc_fortran VERSION 0.0.1 DESCRIPTION "Write some thicc Fortran." LANGUAGES Fortran)

set(CMAKE_Fortran_STANDARD 2003)
set(CMAKE_Fortran_EXTENSIONS OFF)
set(CMAKE_Fortran_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} include/${PROJECT_NAME}.f03)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SUPERPROJECT_NAME})

add_executable(${PROJECT_NAME}_demo demo.f03)
set_target_properties(${PROJECT_NAME}_demo PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT 20)