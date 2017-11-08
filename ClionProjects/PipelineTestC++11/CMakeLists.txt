cmake_minimum_required(VERSION 3.3)
project(PipelineTestC__11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PipelineStage.cpp PipelineStage.h PipelineController.cpp PipelineController.h)
add_executable(PipelineTestC__11 ${SOURCE_FILES})