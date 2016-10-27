cmake_minimum_required(VERSION 3.6)
project(CACHE)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main.cpp
                 Request.cpp
                 Cache.cpp
                 Lru.cpp
                 PartitionedCache.cpp
                 Pareto.cpp
                 StackDistFlow.cpp
                 TraceFileFlow.cpp
                 Utils/ConsoleLogger.cpp
                 Utils/FileLogger.cpp
                 Utils/Logger.cpp
                 Utils/Utils.cpp)

set(HEADER_FILES Request.h
                 Cache.h
                 Lru.h
                 PartitionedCache.h
                 Flow.h
                 Pareto.h
                 StackDistFlow.h
                 TraceFileFlow.h
                 Utils/Types.h
                 Utils/ConsoleLogger.h
                 Utils/FileLogger.h
                 Utils/Logger.h
                 Utils/Utils.h)

add_executable(CACHE ${SOURCE_FILES})