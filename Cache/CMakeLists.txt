cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
                 Main/Main.cpp

                 Main/Modes/AnalyzeMode.cpp
                 Main/Modes/GenerateMode.cpp
                 Main/Modes/SimulateMode.cpp

                 Math/LeastSquareMethod.cpp

                 Storages/Storage.cpp
                 Storages/SharedStorage.cpp
                 Storages/StaticPartial.cpp
                 Storages/DynamicPartial.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp

                 Requests/Request.cpp

                 Generators/Pareto.cpp
                 Generators/TimeGen.cpp
                 Generators/StackDistance.cpp
                 Generators/LbaGen.cpp
                 Generators/RandomValue.cpp
                 Generators/UniformReal.cpp
                 Generators/UniformInt.cpp
                 Generators/Exponential.cpp

                 Flows/Flow.cpp
                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Clients/Client.cpp
                 Clients/ClientsManager.cpp

                 Modeling/TraceAnalyzer.cpp

                 Loggers/ConsoleLogger.cpp
                 Loggers/FileLogger.cpp
                 Loggers/Logger.cpp

                 Utils/Utils.cpp
                 Utils/GnuPlot.cpp

                 Libs/pugixml.cpp

                 Xml/MainConfig.cpp
                 Xml/AnalyzeConfig.cpp

                 Xml/XmlModes/XmlAnalyzeMode.cpp
                 Xml/XmlModes/XmlGenerateMode.cpp
                 Xml/XmlModes/XmlSimulateMode.cpp
                 )

set(HEADER_FILES
                 Main/Modes/ModeRunner.h

                 Math/LeastSquareMethod.h

                 Storages/Storage.h
                 Storages/SharedCache.h
                 Storages/StaticPartial.h
                 Storages/DynamicPartial.h

                 Caches/Cache.h
                 Caches/Lru.h

                 Requests/Request.h

                 Generators/Pareto.h
                 Generators/TimeGen.h
                 Generators/RandomValue.h
                 Generators/StackDistance.h
                 Generators/LbaGen.h
                 Generators/UniformReal.h
                 Generators/UniformInt.h
                 Generators/Exponential.h

                 Flows/Flow.h
                 Flows/StackDistFlow.h
                 Flows/TraceFileFlow.h

                 Clients/Client.h
                 Clients/ClientsManager.h

                 Modeling/TraceAnalyzer.h

                 Utils/Types.h
                 Utils/Utils.h
                 Utils/GnuPlot.h
                 Utils/Paths.h

                 Libs/pugiconfig.hpp
                 Libs/pugixml.hpp

                 Xml/MainConfig.h
                 Xml/AnalyzeConfig.h

                 Xml/XmlModes/XmlAnalyzeMode.h
                 Xml/XmlModes/XmlGenerateMode.h
                 Xml/XmlModes/XmlSimulateMode.h

                 Loggers/ConsoleLogger.h
                 Loggers/FileLogger.h
                 Loggers/Logger.h
                 )

add_executable(Cache ${SOURCE_FILES})