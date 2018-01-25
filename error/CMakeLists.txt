set(LIB_NAME error)

set(HEADERS
    Instigator.hpp
    Error.hpp
)

set(SOURCES
    Instigator.cpp
    Error.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
