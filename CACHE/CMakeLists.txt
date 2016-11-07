cmake_minimum_required(VERSION 3.6)
project(CACHE)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp
                 Caches/PartitionedCache.cpp

                 Generators/Request.cpp
                 Generators/Pareto.cpp

                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 )

set(HEADER_FILES
                 Caches/Cache.h
                 Caches/Lru.h
                 Caches/PartitionedCache.h

                 Generators/Request.h
                 Generators/Pareto.h

                 Flows/Flow.h
                 Flows/StackDistFlow.h
                 Flows/TraceFileFlow.h

                 Utils/Types.h
                 Utils/Utils.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(CACHE ${SOURCE_FILES})