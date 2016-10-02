cmake_minimum_required(VERSION 3.6)
project(CACHE)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main.cpp
                 Request.cpp
                 Cache.cpp
                 Lru.cpp
                 ConsoleLogger.cpp
                 Flow.cpp
                 DistributionGenerator.cpp
                 Utils.cpp)

set(HEADER_FILES Request.h
                 Cache.h
                 Lru.h
                 ConsoleLogger.h
                 Flow.h
                 DistributionGenerator.h
                 Utils.h)

add_executable(CACHE ${SOURCE_FILES})