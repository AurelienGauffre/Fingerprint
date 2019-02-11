#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo optimization rtxy :" << std::endl ;
  std::string m_name1, m_name2;
  if (argc == 3){
    m_name1 = (std::string)argv[1];
    m_name2 = (std::string)argv[2];
  }
  else{
    m_name1 = "../ressources/clean_finger.png" ;
    m_name2 = "../ressources/rtxy_finger.png" ;
  }
  cv::Mat m_image1;
  m_image1 = cv::imread(m_name1, cv::IMREAD_GRAYSCALE);
  Image im1(m_image1, m_name1);
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);

  float p[3];
  im1.opti_greedy_fast_rxy(p,im2,true);
  std::cout << "After approx, px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  im1.coord_descent(p,im2,true,false);
  std::cout << "After coord_descent, px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;

  im1.translation(p[0],p[1]);
  im1.rotate_bilinear(p[2],Pixel(m_image1.cols/2,m_image1.rows/2));
  Image error = im1.Absolute_error_image(im2);
  error.display_Mat();

  return 0;
}
