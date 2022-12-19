cmake_minimum_required(VERSION 3.23)
project(ThicC VERSION 0.0.1 DESCRIPTION "Write some thicc C." LANGUAGES C)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    if (APPLE)
        set(CMAKE_C_FLAGS "-Weverything -pedantic-errors")
    else ()
        set(CMAKE_C_FLAGS "-Weverything -pedantic-errors")
    endif ()
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic-errors")
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "/Tc /Za /Wall")
endif ()

file(GLOB_RECURSE THICC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "thicc/*.h")
file(GLOB_RECURSE THICC_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "thicc/*.c")
file(GLOB_RECURSE TEST_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "test/*.h")
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "test/*.c")

add_custom_target(npm_install ALL
                  COMMAND npm install
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(thicc STATIC ${THICC_HEADERS} ${THICC_SOURCES})
add_dependencies(thicc npm_install)
target_include_directories(thicc PRIVATE include)
IF(NOT WIN32)
    target_link_libraries(thicc PRIVATE m)
ENDIF()
set_target_properties(thicc PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER include/thicc.h)

configure_file(thicc.pc.in thicc.pc @ONLY)
install(TARGETS thicc
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/thicc.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

add_executable(thicc_test ${TEST_HEADERS} ${TEST_SOURCES})
add_dependencies(thicc_test thicc)
target_link_libraries(thicc_test PRIVATE thicc)
target_include_directories(thicc_test PRIVATE include)

add_executable(thicc_demo demo.c)
add_dependencies(thicc_demo thicc)
target_link_libraries(thicc_demo PRIVATE thicc)
target_include_directories(thicc_demo PRIVATE include)

enable_testing()
add_test(NAME thicc_test
         COMMAND $<TARGET_FILE:thicc_test>)
add_test(NAME thicc_demo_test
         COMMAND $<TARGET_FILE:thicc_demo>)