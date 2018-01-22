function(addLibs target)

set(LIBRARIES
    networkprotocol
    command
    states
)

set(INCLUDES
    ${CMAKE_SOURCE_DIR}/networkprotocol
    ${CMAKE_SOURCE_DIR}/command
    ${CMAKE_SOURCE_DIR}/states
)

target_link_libraries(${target} ${LIBRARIES})
include_directories(${target}, ${INCLUDES})

endfunction(addLibs)
