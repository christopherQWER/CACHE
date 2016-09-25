cmake_minimum_required(VERSION 3.6)
project(CACHE)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES CACHE/Main.cpp CACHE/Request.cpp CACHE/Request.h CACHE/Cache.cpp CACHE/Cache.h CACHE/Lru.cpp CACHE/Lru.h CACHE/ConsoleLogger.cpp CACHE/ConsoleLogger.h CACHE/DistributionGenerator.cpp CACHE/DistributionGenerator.h CACHE/Flow.cpp CACHE/Flow.h Tests/Flow_Test.cpp)
add_executable(CACHE ${SOURCE_FILES})