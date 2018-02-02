set(LIB_NAME states)

set(HEADERS
    AbstractControlState.hpp
    EmergencyState.hpp
    StandbyState.hpp
    PodState.hpp
    states.hpp
    Boot.hpp
)

set(SOURCES
    AbstractControlState.cpp
    EmergencyState.cpp
    StandbyState.cpp
    PodState.cpp
    Boot.cpp
)

add_library(${LIB_NAME} ${HEADERS} ${SOURCES})
includeBoost(${LIB_NAME})
