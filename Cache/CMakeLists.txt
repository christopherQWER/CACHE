cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
                 Main/Main.cpp
                 Main/ModeRunner.cpp

                 Algorithms/Algorithm.cpp
                 Algorithms/SharedCache.cpp
                 Algorithms/StaticPartial.cpp
                 Algorithms/DynamicPartial.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp

                 Generators/Request.cpp
                 Generators/Pareto.cpp
                 Generators/PdfFlow.cpp

                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Modeling/Client.cpp
                 Modeling/TraceAnalyzer.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 Utils/Plot.cpp

                 Xml/pugixml.cpp
                 Xml/MainConfig.cpp
                 Xml/AnalyzeConfig.cpp
        Generators/Distribution.cpp)

set(HEADER_FILES
                 Main/ModeRunner.h

                 Algorithms/Algorithm.h
                 Algorithms/SharedCache.h
                 Algorithms/StaticPartial.h
                 Algorithms/DynamicPartial.h

                 Caches/Cache.h
                 Caches/Lru.h

                 Generators/Request.h
                 Generators/Pareto.h
                 Generators/Distribution.h
                 Generators/PdfFlow.h

                 Flows/Flow.h
                 Flows/StackDistFlow.h
                 Flows/TraceFileFlow.h

                 Modeling/Client.h
                 Modeling/TraceAnalyzer.h

                 Utils/Types.h
                 Utils/Utils.h
                 Utils/Plot.h
                 Utils/Paths.h

                 Xml/pugiconfig.hpp
                 Xml/pugixml.hpp
                 Xml/MainConfig.h
                 Xml/AnalyzeConfig.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(Cache ${SOURCE_FILES})