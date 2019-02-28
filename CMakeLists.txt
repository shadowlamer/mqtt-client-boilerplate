cmake_minimum_required(VERSION 3.0)

set(TARGET mqtt-client-boilerplate)

project(${TARGET})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
set(DTO_PATH "/opt/dto/linux-${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=gnu++11")

file(GLOB_RECURSE A3VODA_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "a3voda/src/*.cpp")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable( ${TARGET} ${A3VODA_SOURCES} ${SOURCES})
set(A3VODA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/a3voda/inc")

find_package (Threads REQUIRED)
find_package (Poco REQUIRED Net Util)
find_package (Mosquitto REQUIRED)
find_package (Mosquittopp REQUIRED)
find_package (rapidjson REQUIRED)

include_directories(inc ${Poco_INCLUDE_DIRS} ${MOSQUITTO_INCLUDE_DIR} ${MOSQUITTOPP_INCLUDE_DIR} ${RAPIDJSON_INCLUDE_DIRS} ${A3VODA_INCLUDE_DIR})
target_link_libraries (${TARGET} ${CMAKE_THREAD_LIBS_INIT} ${Poco_LIBRARIES} ${MOSQUITTO_LIBRARIES} ${MOSQUITTOPP_LIBRARIES})

install(TARGETS ${TARGET} DESTINATION bin)
