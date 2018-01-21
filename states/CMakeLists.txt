set(LIB_NAME states)

set(HEADERS
    states.hpp
    AbstractControlState.hpp
    StandbyState.hpp
    PodState.hpp
)

set(SOURCES
    empty.cpp
    AbstractControlState.cpp
    StandbyState.cpp
    PodState.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
