cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES Main/Main.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp

                 Generators/Request.cpp
                 Generators/Pareto.cpp

                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Modeling/SharedCache.cpp
                 Modeling/Client.cpp
                 Modeling/PartialCache.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 Utils/Plot.cpp
                 Utils/TraceAnalyzer.cpp

                 Xml/pugixml.cpp
                 Xml/XmlConfig.cpp
                 )

set(HEADER_FILES
                 Caches/Cache.h
                 Caches/Lru.h

                 Generators/Request.h
                 Generators/Pareto.h
                 Generators/Distribution.h

                 Flows/Flow.h
                 Flows/StackDistFlow.h
                 Flows/TraceFileFlow.h

                 Modeling/SharedCache.h
                 Modeling/Client.h
                 Modeling/PartialCache.р

                 Utils/Types.h
                 Utils/Utils.h
                 Utils/Plot.h
                 Utils/TraceAnalyzer.h

                 Xml/pugiconfig.hpp
                 Xml/pugixml.hpp
                 Xml/XmlConfig.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(Cache ${SOURCE_FILES})