#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::cout << "Demo optimization :" << std::endl ;
  std::string m_name = (std::string)argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  std::string m_name2 = (std::string)argv[2];
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);

  // float p;
  // std::clock_t start;
  // double duration;
  // start = std::clock();
  // im1.opti_greedy_x(p,im2,true,false);
  // duration = (std::clock()- start)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time : " << duration << std::endl;
  // std::cout << "p : " << p << std::endl;

  // float p[2];
  // std::clock_t start;
  // double duration;
  // start = std::clock();
  // im1.opti_greedy_fast_xy(p,im2,true,false);
  // duration = (std::clock()- start)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time : " << duration << std::endl;
  // std::cout << "px : " << p[0] << "py : " << p[1] << std::endl;

  // float p[2];
  // std::clock_t start;
  // double duration;
  // start = std::clock();
  // im1.opti_subpixel(p,im2,true);
  // duration = (std::clock()- start)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time : " << duration << std::endl;
  // std::cout << "px : " << p[0] << "py : " << p[1] << std::endl;

  float p[3];
  // clock_t start;
  // double duration;
  // start = clock();
  im1.opti_greedy_fast_rxy(p,im2,true);
  // duration = (clock()- start)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time : " << duration << std::endl;
  std::cout << "After approx px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  // clock_t start2;
  // double duration2;
  // start2 = clock();
  im1.coord_descent(p,im2,true,false);
  // duration2 = (clock()- start2)/(double)CLOCKS_PER_SEC;
  // std::cout << "Execution time : " << duration2 << std::endl;
  std::cout << "After coord_descent px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;

  // im1.rotate_bilinear(0.260269,Pixel(128,144));
  // im1.translation(-28,26);
  // im1.save_Mat();
  // Image error = im1.Absolute_error_image(im2);
  // error.save_Mat();

  return 0;
}
