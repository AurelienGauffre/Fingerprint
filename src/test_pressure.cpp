#include <iostream>

#include "test_pressure.hpp"

void test_pressure(char const *arg[]){
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);
  // im1.weight_coeff(128,170);
  //im1.save_Mat();
  im1.weight_coeff_ellipse(0.5);
  im1.save_Mat();
}
