cmake_minimum_required(VERSION 3.6)
project(CACHE)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main.cpp
                 Request.cpp
                 Cache.cpp
                 Lru.cpp
                 Utils/ConsoleLogger.cpp
                 Utils/FileLogger.cpp
                 Flow.cpp
                 DistributionGenerator.cpp
                 Utils/Utils.cpp)

set(HEADER_FILES Request.h
                 Cache.h
                 Lru.h
                 Utils/ConsoleLogger.h
                 Utils/FileLogger.h
                 Flow.h
                 DistributionGenerator.h
                 Utils/Utils.h)

add_executable(CACHE ${SOURCE_FILES})