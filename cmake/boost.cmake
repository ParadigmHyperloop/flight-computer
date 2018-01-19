function(includeBoost libName)

# Get all of the libraries from the libraries folder
set(LIBRARIES
    ${CMAKE_SOURCE_DIR}/lib/libboost_chrono${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_date_time${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_filesystem${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_program_options${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_regex${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_serialization${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_system${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_thread${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_unit_test_framework${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${CMAKE_SOURCE_DIR}/lib/libboost_wserialization${CMAKE_STATIC_LIBRARY_SUFFIX}
)

# Include the massive include folder with boost
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/../include/)

add_compile_options(-DBOOST_SYSTEM_NO_DEPRECATED -DBOOST_ERROR_CODE_HEADER_ONLY)
target_link_libraries(${libName} ${LIBRARIES})

endfunction(includeBoost)
