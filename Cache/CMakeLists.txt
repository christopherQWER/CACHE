cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
                 Main/Main.cpp
                 Main/ModeRunner.cpp

                 Storages/Storage.cpp
                 Storages/SharedStorage.cpp
                 Storages/StaticPartial.cpp
                 Storages/DynamicPartial.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp

                 Generators/Request.cpp
                 Generators/Pareto.cpp
                 Generators/PdfFlow.cpp
                 Generators/Distribution.cpp

                 Flows/Flow.cpp
                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Modeling/Client.cpp
                 Modeling/TraceAnalyzer.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 Utils/Plot.cpp

                 Libs/pugixml.cpp

                 Xml/MainConfig.cpp
                 Xml/AnalyzeConfig.cpp
                 Xml/AnalyzerConfig.cpp
                 Xml/GenerateConfig.cpp
                 Xml/SimulateConfig.cpp
                 )

set(HEADER_FILES
                 Main/ModeRunner.h

                 Storages/Storage.h
                 Storages/SharedCache.h
                 Storages/StaticPartial.h
                 Storages/DynamicPartial.h

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

                 Libs/pugiconfig.hpp
                 Libs/pugixml.hpp

                 Xml/MainConfig.h
                 Xml/AnalyzeConfig.h
                 Xml/AnalyzerConfig.h
                 Xml/GenerateConfig.h
                 Xml/SimulateConfig.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(Cache ${SOURCE_FILES})