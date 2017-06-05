cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../Cache)

set(SOURCE_FILES Main.cpp

                 XmlTest/TestConfig.cpp

                 TestStorages/TestStaticPartial.cpp
                 TestGenerators/TestDistribution.cpp

                 ../Cache/Flows/TraceFileFlow.cpp
                 ../Cache/Flows/StackDistFlow.cpp

                 ../Cache/Clients/Client.cpp
                 ../Cache/Clients/ClientsManager.cpp

                 ../Cache/Generators/StackDistanceGen.cpp
                 ../Cache/Generators/RandomValue.cpp
                 ../Cache/Generators/UniformReal.cpp
                 ../Cache/Generators/UniformInt.cpp
                 ../Cache/Generators/LbaGen.cpp
                 ../Cache/Generators/TimeGen.cpp
                 ../Cache/Generators/SizeGen.cpp
                 ../Cache/Generators/Exponential.cpp
                 ../Cache/Generators/ChiSquare.cpp

                 ../Cache/Requests/Request.cpp
                 ../Cache/Requests/RequestParser.cpp
                 ../Cache/Requests/RequestGenerator.cpp

                 ../Cache/Caches/Cache.cpp
                 ../Cache/Caches/Lru.cpp

                 ../Cache/Storages/Storage.cpp
                 ../Cache/Storages/StaticPartial.cpp

                 ../Cache/Loggers/Logger.cpp
                 ../Cache/Loggers/ConsoleLogger.cpp
                 ../Cache/Loggers/FileLogger.cpp

                 ../Cache/Utils/Utils.cpp
                 ../Cache/Utils/GnuPlot.cpp

                 ../Cache/Modeling/TraceAnalyzer.cpp

                 ../Cache/Xml/MainConfig.cpp
                 ../Cache/Xml/AnalyzeConfig.cpp

                 ../Cache/Libs/pugixml.cpp TestStorages/TestShared.cpp TestStorages/TestShared.h)

set(HEADER_FILES XmlTest/TestConfig.h

                 TestStorages/TestStaticPartial.h
                 TestGenerators/TestDistribution.h

                 ../Cache/Flows/Flow.h
                 ../Cache/Flows/TraceFileFlow.h
                 ../Cache/Flows/StackDistFlow.h

                 ../Cache/Clients/Client.h
                 ../Cache/Clients/ClientsManager.h

                 ../Cache/Caches/Lru.h
                 ../Cache/Caches/Cache.h

                 ../Cache/Storages/Storage.h
                 ../Cache/Storages/StaticPartial.h

                 ../Cache/Generators/StackDistanceGen.h
                 ../Cache/Generators/RandomValue.h
                 ../Cache/Generators/UniformReal.h
                 ../Cache/Generators/UniformInt.h
                 ../Cache/Generators/LbaGen.h
                 ../Cache/Generators/TimeGen.h
                 ../Cache/Generators/SizeGen.h
                 ../Cache/Generators/Exponential.h
                 ../Cache/Generators/ChiSquare.h

                 ../Cache/Requests/Request.h
                 ../Cache/Requests/RequestParser.h
                 ../Cache/Requests/RequestGenerator.h

                 ../Cache/Loggers/Logger.h
                 ../Cache/Loggers/ConsoleLogger.h
                 ../Cache/Loggers/FileLogger.h

                 ../Cache/Utils/Utils.h
                 ../Cache/Utils/Types.h
                 ../Cache/Utils/Paths.h
                 ../Cache/Utils/GnuPlot.h

                 ../Cache/Modeling/TraceAnalyzer.h

                 ../Cache/Xml/MainConfig.h
                 ../Cache/Xml/AnalyzeConfig.h

                 ../Cache/Libs/pugixml.hpp)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})