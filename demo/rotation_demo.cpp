#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::cout << "Demo rotation :" << std::endl ;
  float angle = M_PI/4;
  Pixel rot_point(128,144);
  std::string m_name = (std::string)argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.rotate_bilinear(angle,rot_point);
  // im1.display_Mat();
  im1.save_Mat();
  return 0;
}
