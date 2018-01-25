cmake_minimum_required(VERSION 3.8)
project(FlightCP)

set(CMAKE_CXX_STANDARD 17)

# Include the Boost include funcion
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(boost)
include(libs)

enable_testing()

add_subdirectory(error)
add_subdirectory(networkprotocol)
add_subdirectory(command)
#add_subdirectory(states)
add_subdirectory(tests)
#add_subdirectory(core)
