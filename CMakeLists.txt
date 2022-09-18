cmake_minimum_required(VERSION 3.5.1)

project(log_reader)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(SOURCES 
    main.cpp 
    args.cpp 
    task.cpp 
    data.cpp 
    parsed_line.cpp 
    thread_pool.cpp)

add_executable(log_reader ${SOURCES})

target_link_libraries(log_reader ${JSONCPP_LIBRARIES})
