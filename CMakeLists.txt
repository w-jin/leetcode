cmake_minimum_required(VERSION 3.10)
project(leetcode)

set(CMAKE_CXX_STANDARD 11)

if (APPLE OR UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -pthread")
endif()

include_directories(include)

file(GLOB SRC_LIST src/*.cpp)

foreach(file ${SRC_LIST})
    # file类似于/d/workspace/leetcode/112_path_sum.cpp，把目录和后缀去掉作为目标名称
    # 如/d/workspace/leetcode/112_path_sum.cpp对应的目标名称为112_path_sum
    string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src/" "" target_name ${file})
    string(REGEX REPLACE ".cpp" "" target_name ${target_name})
    add_executable(${target_name} ${file})
endforeach()
