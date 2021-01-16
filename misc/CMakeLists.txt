cmake_minimum_required(VERSION 2.8)
project(zpl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories("../code/")

set(example_dir "../code/apps/examples")
file(GLOB examples ${example_dir}/*)

foreach(example_source ${examples})
    get_filename_component(example_name ${example_source} NAME)
    string(REPLACE ".c" "${OUTPUT_EXT}" example_name ${example_name})

    # Setup the example
    add_executable(${example_name} ${example_source})

    if (WIN32)
        target_link_libraries(${example_name} winmm)
    elseif (UNIX)
        target_link_libraries(${example_name} pthread m dl atomic)
    endif()
endforeach()

add_executable(tester ../code/tests/tester.c)

if (WIN32)
    target_link_libraries(tester winmm)
elseif (APPLE)
    target_link_libraries(tester pthread m dl)
elseif (UNIX)
    target_link_libraries(tester pthread m dl atomic)
endif()
