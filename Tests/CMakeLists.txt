cmake_minimum_required(VERSION 3.6)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
include_directories(INCLUDE_DIR ../CACHE)

set(SOURCE_FILES Main.cpp
                 TestFlow.cpp
                 ../CACHE/Flow.cpp
                 ../CACHE/Lru.cpp
                 ../CACHE/Generator.cpp
                 ../CACHE/Request.cpp
                 ../CACHE/Cache.cpp
                 ../CACHE/Utils/Logger.cpp
                 ../CACHE/Utils/ConsoleLogger.cpp
                 ../CACHE/Utils/FileLogger.cpp
                 ../CACHE/Utils/Utils.cpp)

set(HEADER_FILES TestFlow.h
                 ../CACHE/Flow.h
                 ../CACHE/Lru.h
                 ../CACHE/Generator.h
                 ../CACHE/Request.h
                 ../CACHE/Cache.h
                 ../CACHE/Utils/Logger.h
                 ../CACHE/Utils/ConsoleLogger.h
                 ../CACHE/Utils/FileLogger.h
                 ../CACHE/Utils/Utils.h)

add_executable(Tests ${SOURCE_FILES} ${INCLUDE_DIR})