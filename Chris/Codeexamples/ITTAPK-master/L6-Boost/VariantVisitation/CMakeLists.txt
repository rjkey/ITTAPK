cmake_minimum_required(VERSION 3.6)
project(VariantVisitation)

find_package(Boost 1.60.0)

if (Boost_FOUND)
    message(${Boost_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(VariantVisitation ${SOURCE_FILES})
