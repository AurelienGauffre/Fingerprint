#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::cout << "Demo warp :" << std::endl ;
  float strength = M_PI/6;
  Pixel location(110,120);
  float radius = 50;
  int violence = 4;
  std::string m_name = (std::string)argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  im1.warp(strength, location, radius, violence);
  im1.display_Mat();
  im1.save_Mat();
  return 0;
}
