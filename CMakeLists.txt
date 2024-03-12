cmake_minimum_required(VERSION 3.18..3.20)

project(TrappingRainwaterII)

# find_package(boost REQUIRED)

add_executable(MyApp HeapSort.cpp Solution.cpp main.cpp)

target_sources(MyApp PRIVATE HeapSort.h Solution.h)   

target_link_libraries(MyApp readline)