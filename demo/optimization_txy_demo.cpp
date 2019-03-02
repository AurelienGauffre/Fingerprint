#include "image.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Demo optimization txy :" << std::endl ;
  std::string m_name1, m_name2;
  if (argc == 3){
    m_name1 = (std::string)argv[1];
    m_name2 = (std::string)argv[2];
  }
  else{
    m_name1 = "../ressources/clean_finger.png" ;
    m_name2 = "../ressources/txy_finger.png" ;
  }
  cv::Mat m_image1;
  m_image1 = cv::imread(m_name1, cv::IMREAD_GRAYSCALE);
  Image im1(m_image1, m_name1);
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);

  // float p1[2];
  // clock_t start1;
  // double duration1;
  // start1 = clock();
  // im1.opti_greedy_xy(p1,im2,true);
  // duration1 = (clock()- start1)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time for greedy : " << duration1 << std::endl;
  // std::cout << "After opti_greedy_xy, px : " << p1[0] << "py : " << p1[1] << std::endl;

  float p[2];
  clock_t start;
  double duration;
  start = clock();
  im1.opti_greedy_fast_xy(p,im2,true,false);
  duration = (clock()- start)/(double)CLOCKS_PER_SEC;
  std::cout << "Execution time for greedy fast : " << duration << std::endl;
  std::cout << "After opti_greedy_fast_xy, px : " << p[0] << " py : " << p[1] << std::endl;
  im1.opti_subpixel(p,im2,true);
  std::cout << "After opti_subpixel, px : " << p[0] << " py : " << p[1] << std::endl;

  im1.translation(p[0],p[1]);
  Image error = im1.Absolute_error_image(im2);
  error.display_Mat();

  return 0;
}
