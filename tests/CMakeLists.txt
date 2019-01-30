# Add this line to the CMakeLists.txt containing tests
add_executable(test_optimization test_optimization.cxx)
target_link_libraries(test_optimization gtest  ${OpenCV_LIBRARIES} ${Eigen3_LIBS} fingerprint)

add_test (NAME optimization_test
    COMMAND test_optimization
    )
