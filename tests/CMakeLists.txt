set(EXNAME tests)
set(COMMANDNAME check)

set(SOURCES
    test.cpp
    test-networkprotocol.cpp
)

add_executable(${EXNAME} ${SOURCES})

addLibs(${EXNAME})
includeBoost(${EXNAME})

add_test(${EXNAME} ${EXNAME})

add_custom_target(${COMMANDNAME}
                  COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
                  ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  DEPENDS ${EXNAME})
