#include "image.hpp"

int main(int argc, char const *argv[]) {

  std::string m_name;
  std::cout << "Demo warp :" << std::endl ;
  if (argc == 1){
    m_name = "../ressources/Swirl1/1.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }
  float strength = -M_PI*3/12;
  Pixel location(160,330);
  float radius = 70;
  int violence = 2;

  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  im1.warp(strength, location, radius, violence);
  im1.display_Mat();
//  im1.save_Mat("Swirl.png");
  return 0;
}
