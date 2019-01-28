add_executable(fingerprints fingerprint.cpp)
add_executable(gaussian_blur gaussian_blur.cpp)
target_link_libraries(fingerprints ${OpenCV_LIBRARIES} ${Eigen3_LIBS} fingerprint)
target_link_libraries(gaussian_blur ${OpenCV_LIBRARIES} ${Eigen3_LIBS} fingerprint)
