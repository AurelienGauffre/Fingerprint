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
  im1.display_Mat();
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
  // std::cout << p[0] << " " << p[1] << std::endl;
  // im1.translation(p[0],p[1]);
  // Image error = im1.Absolute_error_image(im2);
  // error.save_Mat();

  im2.rotate_bilinear(0.44,Pixel(125,140,0));
  im2.display_Mat();
  std::vector<float> p = im1.opti_rot(im2,false);

  // std::vector<float> p_0 {20,20,0.5};
  // im1.coord_descent(p_0,im2,true);

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

void test_convolute_dft(char const *arg[],std::vector<float> kernel)
{
  std::string m_name = (std::string)arg[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.convolute_dft(kernel);

  im1.display_Mat();

}

void test_inv_ft(char const *arg[]) {
    // Load an image
  std::string m_name = (std::string)arg[1];
  cv::Mat inputImage = cv::imread(m_name, 0);

  // Go float
  cv::Mat fImage;
  inputImage.convertTo(fImage, CV_32F);
  std::cout << "1rst convertion ok" << '\n';

  // FFT
  std::cout << "Direct transform...\n";
  cv::Mat fourierTransform;
  cv::dft(fImage, fourierTransform, cv::DFT_SCALE|cv::DFT_COMPLEX_OUTPUT);
  std::cout << "Fourier tf ok" << '\n';
  //std::cout << fourierTransform << '\n';


  // IFFT
  std::cout << "Inverse transform...\n";
  cv::Mat inverseTransform;
  cv::dft(fourierTransform, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);

  //Back to 8-bits
  cv::Mat finalImage;
  fourierTransform.convertTo(finalImage, CV_8U);
  std::cout << "2nd convertion ok" << '\n';
  std::cout << finalImage << '\n';

  cv::namedWindow("result.png", 100000);
  cv::imshow("result.png", finalImage);
  cv::waitKey(0);
}
