cmake_minimum_required(VERSION 3.6)
project(TimerCallback)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(SOURCE_FILES Events.cpp Timer.cpp Bindfunction.cpp)
add_executable(TimerCallback ${SOURCE_FILES})
