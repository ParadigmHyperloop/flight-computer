set(LIB_NAME networkprotocol)

set(HEADERS
    Connection.hpp
    networkprotocol.hpp
    NRetryProtocol.hpp
    RetryProtocol.hpp
    SimpleRetryProtocol.hpp
)

set(SOURCES
    Connection.cpp
    empty.cpp
    NRetryProtocol.cpp
    RetryProtocol.cpp
    SimpleRetryProtocol.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
addError(${LIB_NAME})
