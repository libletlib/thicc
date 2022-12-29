cmake_minimum_required(VERSION 3.23)
enable_language(Fortran)
project(thicc_fortran VERSION 0.0.1 DESCRIPTION "Write some thicc Fortran." LANGUAGES Fortran)

set(CMAKE_Fortran_STANDARD 2003)
set(CMAKE_Fortran_EXTENSIONS OFF)
set(CMAKE_Fortran_STANDARD_REQUIRED ON)
set(BOILERPLATE_NAME ${PROJECT_NAME}_boilerplate)

file(GLOB_RECURSE BOILERPLATE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/fortran "${SOURCE_DIRECTORY}/*.c")

add_library(${BOILERPLATE_NAME} ${BOILERPLATE_SOURCES})
target_link_libraries(${BOILERPLATE_NAME} PRIVATE ${SUPERPROJECT_NAME})
target_include_directories(${BOILERPLATE_NAME} PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})

add_library(${PROJECT_NAME} ${SOURCE_DIRECTORY}/${PROJECT_NAME}.F03)
add_compile_definitions(THICC_FORTRAN_VERSION=${CMAKE_Fortran_STANDARD})
add_compile_definitions(THICC_FORTRAN_C_VERSION=${CMAKE_C_STANDARD})
target_include_directories(${BOILERPLATE_NAME} PRIVATE ../${HEADER_DIRECTORY})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(${PROJECT_NAME} PRIVATE ${BOILERPLATE_NAME})

add_executable(${PROJECT_NAME}_demo demo.f03)
set_target_properties(${PROJECT_NAME}_demo PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})