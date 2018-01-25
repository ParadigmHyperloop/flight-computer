set(LIB_ERROR error)
set(INC_ERROR ${CMAKE_SOURCE_DIR}/error)

set(LIBRARIES
    networkprotocol
    command
)


set(INCLUDES
    ${CMAKE_SOURCE_DIR}/networkprotocol
    ${CMAKE_SOURCE_DIR}/command
    ${CMAKE_SOURCE_DIR}/states
)


# Adds the error library to a target
function(addError target)

target_link_libraries(${target} ${LIB_ERROR})
include_directories(${target}, ${INC_ERROR})

endfunction(addError)


# Adds all of the libraries (excluding error to the target 
function(addLibs target)

target_link_libraries(${target} ${LIBRARIES})
include_directories(${target}, ${INCLUDES})

endfunction(addLibs)
