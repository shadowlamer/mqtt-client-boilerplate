cmake_minimum_required(VERSION 3.0)

message("Processor: ${CMAKE_SYSTEM_PROCESSOR}")

set(DEMO_TARGET mqtt-client-demo)
set(LIB_TARGET a3voda)
set(TEST_TARGET a3voda-test)
set(LIB_VERSION "0.0.1")

project(${LIB_TARGET})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=gnu++11")

#Find libraries
find_package (Threads REQUIRED)
find_package (Poco REQUIRED Net Util)
find_package (Mosquitto REQUIRED)
find_package (Mosquittopp REQUIRED)
find_package (rapidjson REQUIRED)

include_directories(${Poco_INCLUDE_DIRS} ${MOSQUITTO_INCLUDE_DIR} ${MOSQUITTOPP_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIRS})
link_libraries (${CMAKE_THREAD_LIBS_INIT} ${Poco_LIBRARIES} ${MOSQUITTO_LIBRARIES} ${MOSQUITTOPP_LIBRARIES})

#Library
file(GLOB_RECURSE LIB_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "a3voda/src/*.cpp")
file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "a3voda/inc/*.h")
add_library( ${LIB_TARGET} SHARED ${LIB_SOURCES})
set(LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/a3voda/inc")
target_include_directories(${LIB_TARGET} PUBLIC ${LIB_INCLUDE_DIR})
set_target_properties(${LIB_TARGET} PROPERTIES PUBLIC_HEADER "${LIB_HEADERS}")
set_target_properties(${LIB_TARGET} PROPERTIES SOVERSION "${LIB_VERSION}")

#Demo
file(GLOB_RECURSE DEMO_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable( ${DEMO_TARGET} ${DEMO_SOURCES})
set(DEMO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/inc")
target_link_libraries (${DEMO_TARGET} ${LIB_TARGET})
target_include_directories(${DEMO_TARGET} PUBLIC ${DEMO_INCLUDE_DIR})

#Tests
file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "tests/src/*.cpp")
file(GLOB_RECURSE TEST_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "tests/inc/*.h")
add_executable(${TEST_TARGET} ${TEST_SOURCES})
set(TEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tests/inc")
target_link_libraries (${TEST_TARGET} ${LIB_TARGET})
target_include_directories(${TEST_TARGET} PUBLIC ${TEST_INCLUDE_DIR} ${LIB_INCLUDE_DIR})

install(TARGETS ${LIB_TARGET}
    LIBRARY DESTINATION lib 
    PUBLIC_HEADER DESTINATION include/a3voda
)

if (NOT DEFINED PACKAGE_ARCHITECTURE)
execute_process (
    COMMAND dpkg --print-architecture
    OUTPUT_VARIABLE PACKAGE_ARCHITECTURE 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
endif()

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "${LIB_TARGET}-dev")
set(CPACK_PACKAGE_VERSION "${LIB_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Vadim Cherenev <sl@anhot.ru>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Functions for interfacing with 3voda vending machines. Visit https://3voda.ru")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libpoco-dev:${PACKAGE_ARCHITECTURE},libmosquitto-dev:${PACKAGE_ARCHITECTURE},libmosquittopp-dev:${PACKAGE_ARCHITECTURE},rapidjson-dev")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${PACKAGE_ARCHITECTURE}")
set(CPACK_PACKAGING_INSTALL_PREFIX "usr")

include(CPack)

enable_testing()
add_test(NAME MyAwesomeTest COMMAND a3voda-test)
