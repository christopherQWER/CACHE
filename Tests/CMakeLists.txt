cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../CACHE)

set(SOURCE_FILES Main.cpp
                 TestFlow.cpp
                 TestDistribution.cpp

                 ../CACHE/Flows/TraceFileFlow.cpp
                 ../CACHE/Flows/StackDistFlow.cpp

                 ../CACHE/Generators/Pareto.cpp
                 ../CACHE/Generators/Request.cpp

                 ../CACHE/Caches/Cache.cpp
                 ../CACHE/Caches/Lru.cpp

                 ../CACHE/Loggers/Logger.cpp
                 ../CACHE/Loggers/ConsoleLogger.cpp
                 ../CACHE/Loggers/FileLogger.cpp

                 ../CACHE/Utils/Utils.cpp)

set(HEADER_FILES TestFlow.h
                 TestDistribution.h

                 ../CACHE/Flows/Flow.h
                 ../CACHE/Flows/TraceFileFlow.h
                 ../CACHE/Flows/StackDistFlow.h

                 ../CACHE/Caches/Lru.h
                 ../CACHE/Caches/Cache.h

                 ../CACHE/Generators/Pareto.h
                 ../CACHE/Generators/Request.h

                 ../CACHE/Loggers/Logger.h
                 ../CACHE/Loggers/ConsoleLogger.h
                 ../CACHE/Loggers/FileLogger.h

                 ../CACHE/Utils/Utils.h
                 ../CACHE/Utils/Types.h)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})