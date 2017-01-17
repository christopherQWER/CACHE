cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp
                 Caches/PartitionedCache.cpp

                 Generators/Request.cpp
                 Generators/Pareto.cpp
                 Generators/Distribution.cpp

                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 Utils/Plot.cpp
                 )

set(HEADER_FILES
                 Caches/Cache.h
                 Caches/Lru.h
                 Caches/PartitionedCache.h

                 Generators/Request.h
                 Generators/Pareto.h
                 Generators/Distribution.h

                 Flows/Flow.h
                 Flows/StackDistFlow.h
                 Flows/TraceFileFlow.h

                 Utils/Types.h
                 Utils/Utils.h
                 Utils/Plot.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(CACHE ${SOURCE_FILES})