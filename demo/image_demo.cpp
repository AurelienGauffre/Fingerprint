#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo image :" << std::endl ;
  std::string m_name;
  if (argc == 2){
    m_name = (std::string)argv[1];
  }
  else{
    m_name = "../ressources/clean_finger.png" ;
  }
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);

  Image im2(im1);
  int origine[2] = {30,0};
  im1.draw_rectangle(1,origine,30,300);
  im2.symetry_x();
  im2.display_Mat();
  im1.display_Mat();

  return 0;

}
