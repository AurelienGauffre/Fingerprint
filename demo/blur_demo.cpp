#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {
  cv::Mat m_image1;
  std::string m_name ;
  if (argc == 1){
    m_name = "../ressources/Rotation4/5.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }

  m_image1 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image1, m_name);
  im1.convolute_blur(5,5); // convolute blur(kernel_radius,speed)
  im1.display_Mat();
  return 0;
}
