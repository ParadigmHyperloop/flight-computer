set(LIB_NAME networkprotocol)

set(HEADERS
    networkprotocol.hpp
    RetryProtocol.hpp
)

set(SOURCES
    empty.cpp
    RetryProtocol.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
