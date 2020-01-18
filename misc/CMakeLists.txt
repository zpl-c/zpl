cmake_minimum_required(VERSION 2.8)
project(zpl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("../code/")

set(example_dir "../code/apps/examples")
file(GLOB examples ${example_dir}/*)

foreach(example_source ${examples})
    get_filename_component(example_name ${example_source} NAME)
    string(REPLACE ".c" "${OUTPUT_EXT}" example_name ${example_name})

    # Setup the example
    add_executable(${example_name} ${example_source})

    if (UNIX)
        target_link_libraries(${example_name} pthread m dl)
    endif()
endforeach()

add_executable(zpl_unit ../code/apps/tests/tester.c)
target_link_libraries(zpl_unit pthread m dl)
