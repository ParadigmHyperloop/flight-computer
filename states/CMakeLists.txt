set(LIB_NAME states)

set(HEADERS
    states.hpp
)

set(SOURCES
    empty.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
