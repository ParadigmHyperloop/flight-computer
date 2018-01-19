cmake_minimum_required(VERSION 3.8)
project(FlightCP)

set(CMAKE_CXX_STANDARD 17)

# Include all of the .hpp, .cpp and .h files in the SRC folder
FILE(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.h*)
FILE(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Get all of the libraries from the libraries folder
FILE(GLOB_RECURSE LIBRARIES ${CMAKE_SOURCE_DIR}/lib/*${CMAKE_STATIC_LIBRARY_SUFFIX})
message(WARNING ${LIBRARIES})

# Include stuff
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options(-DBOOST_SYSTEM_NO_DEPRECATED -DBOOST_ERROR_CODE_HEADER_ONLY)

add_executable(FlightCP ${HS} ${SOURCES})