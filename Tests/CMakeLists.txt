cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
include_directories(INCLUDE_DIR ../Cache)

set(SOURCE_FILES Main.cpp
                 TestFlow.cpp
                 TestConfig.cpp
                 TestDistribution.cpp

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
                 ../Cache/Utils/Plot.cpp
                 ../Cache/Utils/TraceAnalyzer.cpp

                 ../Cache/Xml/XmlConfig.cpp)

set(HEADER_FILES TestFlow.h
                 TestConfig.h
                 TestDistribution.h

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
                 ../Cache/Utils/Paths.h
                 ../Cache/Utils/Plot.h
                 ../Cache/Utils/TraceAnalyzer.h

                 ../Cache/Xml/XmlConfig.h
                 ../Cache/Xml/pugixml.hpp)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})