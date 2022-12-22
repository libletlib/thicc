cmake_minimum_required(VERSION 3.23)
enable_language(C)
project(thicc VERSION 0.0.1 DESCRIPTION "Write some thicc C." LANGUAGES C)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(SUPERPROJECT_NAME ${PROJECT_NAME})

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

file(GLOB_RECURSE THICC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE THICC_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE TEST_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "test/*.h")
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "test/*.c")

add_custom_target(npm_install ALL
                  COMMAND npm install
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${THICC_HEADERS} ${THICC_SOURCES})
add_dependencies(${PROJECT_NAME} npm_install)
target_include_directories(${PROJECT_NAME} PRIVATE include)
IF(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
ENDIF()
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER include/${PROJECT_NAME}.h)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
install(TARGETS thicc
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

add_executable(${PROJECT_NAME}_test ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)

add_executable(${PROJECT_NAME}_demo demo.c)
target_link_libraries(${PROJECT_NAME}_demo PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_demo PRIVATE include)

add_subdirectory(cpp)
add_subdirectory(fortran)
add_subdirectory(objc)

enable_testing()
add_test(NAME ${PROJECT_NAME}_test
         COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>)
set_tests_properties(${PROJECT_NAME}_test PROPERTIES TIMEOUT 20)
add_test(NAME ${PROJECT_NAME}_demo_test
         COMMAND $<TARGET_FILE:${PROJECT_NAME}_demo>)
set_tests_properties(${PROJECT_NAME}_demo_test PROPERTIES TIMEOUT 20)