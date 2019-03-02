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
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Pixel location(160,330);
  float radius = 70;
  int violence = 2;
  for (float i = 1; i<=8.0; i++) {
    float strength = -M_PI*i/24;
    std::cout<< "Warp of " << i/24*180 << " degrees."<<std::endl;
    cv::Mat m_im1 = m_image.clone();
    Image im1(m_im1, m_name);
    im1.warp(strength, location, radius, violence);
    im1.save_Mat();
    im1.display_Mat();
  }
  return 0;


}
