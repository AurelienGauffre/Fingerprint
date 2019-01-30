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
  // float p[2];
  // im1.opti_subpixel(p,im2,true);
  // std::cout << "px : " << p[0] << "py : " << p[1] << std::endl;
  im1.translation(-16.5625,21.4375);
  im1.save_Mat();
  Image error = im1.Absolute_error_image(im2);
  error.save_Mat();
  // float p[3];
  // im1.opti_greedy_fast_rxy(p,im2,true);
  // std::cout << "After approx px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  // im1.coord_descent(p,im2,true);
  // std::cout << "After coord_descent px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  // im1.rotate_bilinear(0.260269,Pixel(128,144));
  // im1.translation(-28,26);
  // im1.save_Mat();
  // Image error = im1.Absolute_error_image(im2);
  // error.save_Mat();
  // im2.translation(-18.51,25.51);
  // im2.rotate_bilinear(2,Pixel(13,16,0));
  float p[3];
  im1.opti_greedy_fast_rxy(p,im2,true);
  im1.coord_descent(p,im2,true);
  return 0;
}
