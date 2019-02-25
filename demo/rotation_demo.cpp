#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo rotation :" << std::endl ;
  std::string m_name;
  if (argc == 1){
    m_name = "../ressources/Rotation4/5.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }

  float angle = 2*M_PI/6;
  Pixel rot_point(160,330);
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  im1.rotate_bilinear(angle,rot_point);
  im1.display_Mat();
  //im1.save_Mat("Rotation.png");
  return 0;
}
