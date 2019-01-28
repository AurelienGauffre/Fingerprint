#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::cout << "Demo convolution classic :" << std::endl ;
  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0};
  // std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1,-1};
  std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1};
  std::string m_name = (std::string)argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  im1.convolute_classic(kernel);
  im1.display_Mat();
  std::cout << "Demo convolution inv ft :" << std::endl ;
  std::string m_name2 = (std::string)argv[1];
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name2, cv::IMREAD_GRAYSCALE);
  Image im2(m_image2, m_name2);
  int r = 50;
  float sigma_clip = 6.0;
  cv::Mat kernel2 = createGausFilterMask(cv::Size(cv::getOptimalDFTSize((im2.get_original_image())->cols), cv::getOptimalDFTSize((im1.get_original_image())->rows)), r, sigma_clip);
  cv::Mat convoluted = im2.fourier_convolution(kernel2);
  Image im_result(convoluted, "image_convoluted");
  im_result.display_Mat();
  return 0;
}
