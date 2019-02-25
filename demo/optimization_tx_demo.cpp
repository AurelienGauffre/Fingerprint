#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo optimization tx :" << std::endl ;
  std::string m_name1, m_name2;
  if (argc == 3){
    m_name1 = (std::string)argv[1];
    m_name2 = (std::string)argv[2];
  }
  else{
    m_name1 = "../ressources/clean_finger.png" ;
    m_name2 = "../ressources/tx_finger.png" ;
  }
  cv::Mat m_image1;
  m_image1 = cv::imread(m_name1, cv::IMREAD_GRAYSCALE);
  Image im1(m_image1, m_name1);
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);

  float p;
  im1.opti_greedy_x(p,im2,true,false);
  std::cout << "p_x : " << p << std::endl;

  im1.translation(p,0);
  Image error = im1.Absolute_error_image(im2);
  error.display_Mat();

  return 0;
}
