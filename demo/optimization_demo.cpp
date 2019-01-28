#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::cout << "Demo optimization :" << std::endl ;
  std::string m_name = (std::string)argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  std::string m_name2 = (std::string)argv[2];
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
  return 0;
}
