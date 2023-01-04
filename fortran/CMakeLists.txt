cmake_minimum_required(VERSION 3.23)
enable_language(Fortran)
project(thicc_fortran VERSION 0.0.1 DESCRIPTION "Write some thicc Fortran." LANGUAGES Fortran)

include(FortranCInterface)
FortranCInterface_VERIFY()

set(CMAKE_Fortran_STANDARD 2003)
set(CMAKE_Fortran_EXTENSIONS OFF)
set(CMAKE_Fortran_STANDARD_REQUIRED ON)
set(OPAQUE_NAME ${PROJECT_NAME}_opaque)

file(GLOB_RECURSE OPAQUE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/fortran ${SOURCE_DIRECTORY}/*.c)
file(GLOB_RECURSE BOILERPLATE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/fortran ${SOURCE_DIRECTORY}/*.F03)
file(GLOB_RECURSE BOILERPLATE_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/fortran ${SOURCE_DIRECTORY}/*.h)

add_library(${OPAQUE_NAME} OBJECT ${OPAQUE_SOURCES})
target_include_directories(${OPAQUE_NAME} PRIVATE ../${HEADER_DIRECTORY} ${HEADER_DIRECTORY})
target_link_libraries(${OPAQUE_NAME} PRIVATE ${SUPERPROJECT_NAME})

add_library(${PROJECT_NAME} src/thicc_fortran.F90 src/thicc_fortran_prelude.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPAQUE_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ../${HEADER_DIRECTORY})
add_compile_definitions(THICC_FORTRAN_VERSION=${CMAKE_Fortran_STANDARD})
add_compile_definitions(THICC_FORTRAN_C_VERSION=${CMAKE_C_STANDARD})

add_executable(${PROJECT_NAME}_demo demo.f90)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE ${CMAKE_Fortran_MODULE_DIRECTORY})
set_target_properties(${PROJECT_NAME}_demo PROPERTIES LINKER_LANGUAGE Fortran)

enable_testing()
add_test(NAME ${PROJECT_NAME}_demo_test
        COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT ${TEST_TIMEOUT})