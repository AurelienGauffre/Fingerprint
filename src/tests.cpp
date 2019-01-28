#include <iostream>
#include <opencv2/opencv.hpp>
#include "tests.hpp"


void test_image(char const *arg[]){
  std::string m_name = (std::string) arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  // im1.display_attributes();
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
  im1.display_Mat();
  // im1.data_intensity();
}

void test_pressure(char const *arg[]){
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  im1.weight_coeff(128,170);
  // im1.weight_coeff_ellipse(0.85);
  im1.save_Mat();
  // im1.display_Mat();
}

void test_rotation(char const *arg[], float angle, Pixel rot_point) {
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.rotate_bilinear(angle,rot_point);
  // im1.display_Mat();
  im1.save_Mat();
}

void test_optimization(char const *arg[]){
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  std::string m_name2 = (std::string)arg[2];
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);
  // std::vector<float> p = im1.opti_subpixel(im2,true);
  // Image error = im1.Absolute_error_image(im2);
  // error.save_Mat();
  // im2.translation(-18.51,25.51);
  im2.rotate_bilinear(1.53,Pixel(13,16,0));
  float p[3];
  im1.opti_greedy_fast_rxy(p,im2,true);
  im1.coord_descent(p,im2,true);
}

void test_warp(char const *arg[], float strength, Pixel location, float radius, int violence)
{
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.warp(strength, location, radius, violence);
  im1.display_Mat();
  im1.save_Mat();
}

void test_convolute_classic(char const *arg[],std::vector<float> kernel)
{
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.convolute_classic(kernel);
  im1.display_Mat();
}

void test_convolute_opti(char const *arg[],std::vector<float> kernel_col,std::vector<float> kernel_line){
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.convolute_opti(kernel_col,kernel_line);
  im1.save_Mat();
  im1.display_Mat();

}

void test_inv_ft(char const *arg[]) {
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  int r = 50;
  float sigma_clip = 6.0;
  cv::Mat kernel = createGausFilterMask(cv::Size(cv::getOptimalDFTSize((im1.get_original_image())->cols), cv::getOptimalDFTSize((im1.get_original_image())->rows)), r, sigma_clip);
  cv::Mat convoluted = im1.fourier_convolution(kernel);
  Image im_result(convoluted, "image_convoluted");
  im_result.display_Mat();
}
