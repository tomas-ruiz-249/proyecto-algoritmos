cmake_minimum_required(VERSION 3.5.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/include/*.h")

add_executable(game ${SOURCES})

# target_link_libraries(${PROJECT_NAME} raylib)