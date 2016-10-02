cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../CACHE)

set(SOURCE_FILES Main.cpp
                 ../CACHE/Flow.cpp
                 ../CACHE/DistributionGenerator.cpp
                 ../CACHE/Request.cpp
                 ../CACHE/Utils.cpp)

set(HEADER_FILES ../CACHE/Flow.h
                  ../CACHE/DistributionGenerator.h
                  ../CACHE/Request.h
                  ../CACHE/Utils.h)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})