cmake_minimum_required(VERSION 3.0)

set(DEMO_TARGET mqtt-client-demo)
set(LIB_TARGET a3voda)
set(LIB_VERSION "0.0.1")

project(${LIB_TARGET})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=gnu++11")

file(GLOB_RECURSE LIB_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "a3voda/src/*.cpp")
file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "a3voda/inc/*.h")
file(GLOB_RECURSE DEMO_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable( ${DEMO_TARGET} ${DEMO_SOURCES})
add_library( ${LIB_TARGET} SHARED ${LIB_SOURCES})

set(LIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/a3voda/inc")
set(DEMO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/inc")

find_package (Threads REQUIRED)
find_package (Poco REQUIRED Net Util)
find_package (Mosquitto REQUIRED)
find_package (Mosquittopp REQUIRED)
find_package (rapidjson REQUIRED)

include_directories(${LIB_INCLUDE_DIR} ${DEMO_INCLUDE_DIR} ${Poco_INCLUDE_DIRS} ${MOSQUITTO_INCLUDE_DIR} ${MOSQUITTOPP_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIRS})
target_link_libraries (${DEMO_TARGET} ${LIB_TARGET} ${CMAKE_THREAD_LIBS_INIT} ${Poco_LIBRARIES} ${MOSQUITTO_LIBRARIES} ${MOSQUITTOPP_LIBRARIES})
set_target_properties(${LIB_TARGET} PROPERTIES PUBLIC_HEADER "${LIB_HEADERS}")
set_target_properties(${LIB_TARGET} PROPERTIES SOVERSION "${LIB_VERSION}")

install(TARGETS ${LIB_TARGET} 
    LIBRARY DESTINATION lib 
    PUBLIC_HEADER DESTINATION include/a3voda
)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "${LIB_TARGET}-dev")
set(CPACK_PACKAGE_VERSION "${LIB_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Vadim Cherenev <sl@anhot.ru>")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Functions for interfacing with 3voda vending machines. Visit https://3voda.ru")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libpoco-dev:${CMAKE_SYSTEM_PROCESSOR},libmosquitto-dev:${CMAKE_SYSTEM_PROCESSOR},libmosquittopp-dev:${CMAKE_SYSTEM_PROCESSOR},rapidjson-dev")
set(CPACK_PACKAGING_INSTALL_PREFIX "usr")

include(CPack)
