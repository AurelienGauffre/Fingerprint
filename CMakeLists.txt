cmake_minimum_required(VERSION 3.0.0)

project(fingerprints)

#Compiler definition and options
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Wextra")
#However, the file(GLOB...) allows for wildcard additions:

file(GLOB SOURCES "src/*.cpp")

list( APPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/external
)

# OpenCV
find_package( OpenCV REQUIRED )
list( APPEND PROJ_INCLUDE_DIRS
    ${OpenCV_INCLUDE_DIRS}
)

find_package(Eigen3 REQUIRED)

# Add OpenCV Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenCV_CFLAGS}")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/inc)
MESSAGE(STATUS ${PROJ_LIBRARY_DIRS})

add_executable(fingerprints
	"./src/image.cpp" "./src/pixel.cpp" "./src/pressure" "./src/rotation.cpp" "./src/tests.cpp"  "./src/warpping.cpp" "./src/translation.cpp" "./src/optimization.cpp" "./src/main.cpp"
)
MESSAGE(STATUS ${OpenCV_LIBRARIES})
target_link_libraries(fingerprints ${OpenCV_LIBRARIES})
