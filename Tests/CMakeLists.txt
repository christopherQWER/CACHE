cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../Cache)

set(SOURCE_FILES Main.cpp
                 TestFlow.cpp
                 FileFlowTest.cpp
                 TestDistribution.cpp
                 TraceAnalyzer.cpp

                 ../Cache/Flows/TraceFileFlow.cpp
                 ../Cache/Flows/StackDistFlow.cpp

                 ../Cache/Generators/Pareto.cpp
                 ../Cache/Generators/Request.cpp

                 ../Cache/Caches/Cache.cpp
                 ../Cache/Caches/Lru.cpp

                 ../Cache/Loggers/Logger.cpp
                 ../Cache/Loggers/ConsoleLogger.cpp
                 ../Cache/Loggers/FileLogger.cpp

                 ../Cache/Utils/Utils.cpp
                 ../Cache/Utils/Plot.cpp)

set(HEADER_FILES TestFlow.h
                 FileFlowTest.h
                 Paths.h
                 TestDistribution.h
                 TraceAnalyzer.h

                 ../Cache/Flows/Flow.h
                 ../Cache/Flows/TraceFileFlow.h
                 ../Cache/Flows/StackDistFlow.h

                 ../Cache/Caches/Lru.h
                 ../Cache/Caches/Cache.h

                 ../Cache/Generators/Pareto.h
                 ../Cache/Generators/Request.h

                 ../Cache/Loggers/Logger.h
                 ../Cache/Loggers/ConsoleLogger.h
                 ../Cache/Loggers/FileLogger.h

                 ../Cache/Utils/Utils.h
                 ../Cache/Utils/Types.h
                 ../Cache/Utils/Plot.h)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})