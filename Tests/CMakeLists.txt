cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../CACHE)

set(SOURCE_FILES Main.cpp
                 TestFlow.cpp
                 TestDistribution.cpp
                 ../CACHE/TraceFileFlow.cpp
                 ../CACHE/StackDistFlow.cpp
                 ../CACHE/Lru.cpp
                 ../CACHE/Pareto.cpp
                 ../CACHE/Request.cpp
                 ../CACHE/Cache.cpp
                 ../CACHE/Utils/Logger.cpp
                 ../CACHE/Utils/ConsoleLogger.cpp
                 ../CACHE/Utils/FileLogger.cpp
                 ../CACHE/Utils/Utils.cpp)

set(HEADER_FILES TestFlow.h
                 TestDistribution.h
                 ../CACHE/Flow.h
                 ../CACHE/TraceFileFlow.h
                 ../CACHE/StackDistFlow.h
                 ../CACHE/Lru.h
                 ../CACHE/Pareto.h
                 ../CACHE/Request.h
                 ../CACHE/Cache.h
                 ../CACHE/Utils/Logger.h
                 ../CACHE/Utils/ConsoleLogger.h
                 ../CACHE/Utils/FileLogger.h
                 ../CACHE/Utils/Utils.h
                 ../CACHE/Utils/Types.h)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})