project(Glucose)

cmake_minimum_required(VERSION 3.25)

set(GLUCOSE_EXE_NAME glucose)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Required on linux by opencv, but adding it for later use
find_package( fmt REQUIRED )

#I installed opencv using mingw64, but it should work with pretty much any opencv installation
find_package( OpenCV 4.6 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

#Used for multithreaded logging
find_package( spdlog REQUIRED )

add_executable(${GLUCOSE_EXE_NAME} main.cpp)

target_link_libraries(${GLUCOSE_EXE_NAME} ${OpenCV_LIBS} fmt::fmt spdlog::spdlog)

add_subdirectory(src)