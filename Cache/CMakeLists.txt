cmake_minimum_required(VERSION 3.6)
project(Cache)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR /usr/include/gsl)
set(CMAKE_SHARED_LINKER_FLAGS "-lgsl")

set(SOURCE_FILES
                 Main/Main.cpp

                 Modes/AnalyzeMode.cpp
                 Modes/GenerateMode.cpp
                 Modes/SimulateMode.cpp
                 Modes/Gears.cpp

                 Math/LeastSquareMethod.cpp

                 Storages/Storage.cpp
                 Storages/SharedStorage.cpp
                 Storages/StaticPartial.cpp

                 Caches/Cache.cpp
                 Caches/Lru.cpp

                 Requests/Request.cpp
                 Requests/RequestGenerator.cpp
                 Requests/RequestParser.cpp

                 Generators/Pareto.cpp
                 Generators/ChiSquare.cpp
                 Generators/TimeGen.cpp
                 Generators/SizeGen.cpp
                 Generators/StackDistanceGen.cpp
                 Generators/LbaGen.cpp
                 Generators/RandomValue.cpp
                 Generators/UniformReal.cpp
                 Generators/UniformInt.cpp
                 Generators/Exponential.cpp

                 Flows/StackDistFlow.cpp
                 Flows/TraceFileFlow.cpp

                 Clients/Client.cpp
                 Clients/ClientsManager.cpp

                 Modeling/TraceAnalyzer.cpp
                 Modeling/PlotManager.cpp

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
                 Modes/ModeRunner.h
                 Modes/Gears.h

                 Math/LeastSquareMethod.h

                 Storages/Storage.h
                 Storages/SharedCache.h
                 Storages/StaticPartial.h

                 Caches/Cache.h
                 Caches/Lru.h

                 Requests/Request.h
                 Requests/RequestGenerator.h
                 Requests/RequestParser.h

                 Generators/Pareto.h
                 Generators/ChiSquare.h
                 Generators/TimeGen.h
                 Generators/SizeGen.h
                 Generators/RandomValue.h
                 Generators/StackDistanceGen.h
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
                 Modeling/PlotManager.h

                 Utils/Types.h
                 Utils/Utils.h
                 Utils/GnuPlot.h
                 Utils/Paths.h
                 Utils/Enums.h
                 Utils/DefinedConstants.h

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

                 gsl)

add_executable(Cache ${SOURCE_FILES})
