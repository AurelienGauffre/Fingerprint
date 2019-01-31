#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {
  cv::Mat m_image1;
  std::string m_name ;
  if (argc == 1){
    m_name = "../ressources/woman.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }


  m_image1 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image1, m_name);
  std::cout << "Demo convolution classic :" << std::endl ;
  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0};
  std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1}; //Sobel vertical kernel
  im1.convolute_classic(kernel);
  im1.save_Mat();
  im1.display_Mat();




  return 0;
}
