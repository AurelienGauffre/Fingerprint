#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {

  cv::Mat m_image1;
  std::string m_name = (std::string)argv[1];
  m_image1 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  cv::Mat m_image2;
  m_image2 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);

  // Creation of Gaussian kernels
  int r = 10;
  float sigma_clip = 4.0;
  double sigma = (r/sigma_clip+0.5f);
  cv::Mat kX = cv::getGaussianKernel(2*r+1, sigma, CV_32F); // Get the Gaussian mask from OpenCV
  cv::Mat kY = cv::getGaussianKernel(2*r+1, sigma, CV_32F);
  cv::Size opti_size = cv::Size(cv::getOptimalDFTSize(m_image1.cols), cv::getOptimalDFTSize(m_image1.rows));
  cv::Mat kernel2 = createFilterMask(opti_size, kX, kY); // Kernel used for convolution in Fourier Sapce

  std::vector<float> kernelX = Mat_to_vector(kX);
  std::vector<float> kernelY = Mat_to_vector(kY);


  (void)argc;
  std::cout << "Demo convolution classic :" << std::endl ;
  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0};
  // std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1,-1};
  //std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1};
  Image im1(m_image1, m_name);
  // im1.convolute_opti(kernelY, kernelX);
  // im1.display_Mat();
  //
  //
  // // Fourier convolution
  // std::cout << "Demo convolution  in Fourier Space :" << std::endl ;
  // Image im2(m_image2, m_name);
  // cv::Mat convoluted = im2.fourier_convolution(kernel2);
  // Image im_result(convoluted, "image_convoluted");
  // im_result.display_Mat();
  //
  // // Difference between two results
  // Image diff = im_result.Absolute_error_image(im1);
  // diff.display_Mat();

  im1.convolute_blur(2,1,1);
  im1.display_Mat();
  return 0;
}
