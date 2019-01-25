add_executable(fingerprints main.cpp)
target_link_libraries(fingerprints ${OpenCV_LIBRARIES} ${Eigen3_LIBS} fingerprint)
