cmake_minimum_required(VERSION 3.6)
project(BasicSignals2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost)

if (Boost_FOUND)


set(SOURCE_FILES main.cpp)
add_executable(BasicSignals2 ${SOURCE_FILES})