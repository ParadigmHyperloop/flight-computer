cmake_minimum_required(VERSION 3.8)
project(FlightCP)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(networkprotocol)
add_subdirectory(states)
add_subdirectory(tests)
