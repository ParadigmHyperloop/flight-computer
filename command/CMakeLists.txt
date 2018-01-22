set(LIB_NAME command)

set(HEADERS
    CommandServer.hpp
)

set(SOURCES
    CommandServer.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
