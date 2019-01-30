cmake_minimum_required(VERSION 3.5.0)

project(fingerprints CXX)

#Compiler definition and options
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
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
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/inc)

MESSAGE(STATUS ${PROJ_LIBRARY_DIRS})

add_subdirectory(src)
add_subdirectory(demo)

# Download googletest while doing the configuration
configure_file(CMakeLists.txt.in
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND}
  -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Add googletest when compiling
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

include_directories(${gtest_SOURCE_DIR}/include)

add_subdirectory(tests)

enable_testing ()

# add_executable(fingerprints
# 	"./src/image.cpp" "./src/pixel.cpp" "./src/pressure.cpp" "./src/dft.cpp" "./src/rotation.cpp" "./src/tests.cpp"  "./src/warpping.cpp" "./src/translation.cpp" "./src/optimization.cpp"  "./src/maths_tools.cpp" "./src/linear_filter.cpp" "./src/main.cpp"
# )
# MESSAGE(STATUS ${OpenCV_LIBRARIES})
# target_link_libraries(fingerprints ${OpenCV_LIBRARIES} ${Eigen3_LIBS})
