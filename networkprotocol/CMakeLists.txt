set(LIB_NAME networkprotocol)

set(HEADERS
    networkprotocol.hpp
)

set(SOURCES
    empty.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
