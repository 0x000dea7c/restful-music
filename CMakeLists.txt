cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/source")
set(COMMON_INCLUDE_DIRECTORY ${SOURCE_DIRECTORY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Wmisleading-indentation -march=native -pipe")

project(
  restful-music
  VERSION 0.0.1
  DESCRIPTION "RESTful Music Playlist API"
  LANGUAGES CXX)

find_package(Crow REQUIRED)

find_package(SQLiteCpp REQUIRED)

find_package(Boost REQUIRED COMPONENTS uuid)

find_package(jwt-cpp REQUIRED)

find_package(GTest REQUIRED)

# Libsodium stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(sodium_USE_STATIC_LIBS OFF CACHE BOOL "Link against static libsodium")
find_package(Sodium REQUIRED)

add_subdirectory(source)

add_subdirectory(tests)

target_link_libraries(restful-music PRIVATE SQLiteCpp Crow::Crow Boost::uuid sodium jwt-cpp::jwt-cpp)
