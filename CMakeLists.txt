cmake_minimum_required(VERSION 3.28)
project(VeilFlow)
add_executable(VeilFlow main.cpp)
set(CMAKE_CXX_STANDARD 20)

# nlohmann_json
add_subdirectory(nlohmann_json)

# OpenCV
set(OpenCV_DIR $ENV{OpenCV_DIR})
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(VeilFlow ${OpenCV_LIBS} nlohmann_json::nlohmann_json)