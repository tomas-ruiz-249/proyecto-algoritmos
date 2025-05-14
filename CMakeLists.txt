# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set project name
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Specify the include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src/include   # Your project's include directory
    ${PROJECT_SOURCE_DIR}/include       # Raylib headers
)
link_directories(
    ${PROJECT_SOURCE_DIR}/lib
)

# Specify the Raylib library directory
set(RAYLIB_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# Find all your source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add the executable to be built
add_executable(MyProject ${SOURCES})

# Platform-specific settings
if(WIN32)
    # Windows: Link with the .lib file and ensure dynamic library (.dll) is available
    if(MSVC)
        target_link_libraries(MyProject raylib.lib)  # Static library on Windows
    else()
        target_link_libraries(MyProject raylib)  # Static library on Windows
    endif()
    target_link_libraries(MyProject winmm.dll)
    # Alternatively, for dynamic libraries on Windows, link with the .dll

elseif(UNIX)
    # Linux: Link with the .so file
    # target_link_libraries(MyProject ${RAYLIB_LIB_DIR}/libraylib.so)  # Static or shared library on Linux
    target_link_libraries(MyProject librayliblinux.a)
endif()

