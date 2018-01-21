set(LIB_NAME networkprotocol)

set(HEADERS
    Connection.hpp
    networkprotocol.hpp
    NRetryProtocol.hpp
    RetryProtocol.hpp
)

set(SOURCES
    Connection.cpp
    empty.cpp
    NRetryProtocol.cpp
    RetryProtocol.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
