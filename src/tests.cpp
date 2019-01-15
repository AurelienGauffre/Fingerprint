#include <iostream>
#include <opencv2/opencv.hpp>
#include "tests.hpp"


void test_image(char const *arg[]){
  std::string m_name = (std::string) arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);
  //im1.display_attributes();
  // im1.display_Mat();
  // im1.save_Mat();
  // im1.save_Mat("other_name.png");
  // std::cout << im1.min_intensity() << im1.max_intensity() << std::endl;
  // unsigned int origine[2] = {30,0};
  // im1.draw_rectangle(1,origine,30,300);
  // im1.draw_rectangle(0,origine,10,10);
  // im1.display_Mat();
  // im1.symetry_y();
  // im1.display_Mat();
  // im1.symetry_diag();
  //
  // im1.display_Mat();
}

void test_pressure(char const *arg[]){
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);
  // im1.weight_coeff(128,170);
  //im1.save_Mat();
  im1.weight_coeff_ellipse(1);
  im1.save_Mat();
}

void test_rotation(char const *arg[], float angle, Pixel rot_point) {
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.rotate_bilinear(angle,rot_point);
  im1.display_Mat();
}

void test_warp(char const *arg[], float strength, Pixel location) {
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.warp(strength, location);
  im1.display_Mat();
}
