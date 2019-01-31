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
  cv::Mat m_image2;
  m_image2 = m_image1.clone();

  // Creation of Gaussian kernels
  int r = 10;
  float sigma_clip = 4.0;
  double sigma = (r/sigma_clip+0.5f);
  cv::Mat kX = cv::getGaussianKernel(2*r+1, sigma, CV_32F); // Get the Gaussian mask from OpenCV
  std::cout << "Sum of kernel X : " << cv::sum(kX)[0] << '\n';
  cv::Mat kY = cv::getGaussianKernel(2*r+1, sigma, CV_32F);
  std::cout << "Sum of kernel Y : " << cv::sum(kY)[0] << '\n';
  cv::Size opti_size = cv::Size(cv::getOptimalDFTSize(m_image1.cols), cv::getOptimalDFTSize(m_image1.rows));
  cv::Mat kernel2 = createFilterMask(opti_size, kX, kY); // Kernel used for convolution in Fourier Sapce
  std::cout << "Sum of kernel : " << cv::sum(kernel2)[0] << '\n';
  cv::imshow("kernel.png", kernel2*100);

  std::vector<float> kernelX = Mat_to_vector(kX);
  std::vector<float> kernelY = Mat_to_vector(kY);

  // Usual convolution
  (void)argc;
  std::cout << "Demo convolution classic :" << std::endl ;
  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0};
  // std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1,-1};
  //std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1};
  Image im1(m_image1, m_name);
  std::clock_t start_classic_conv;
  double duration_classic_conv;
  start_classic_conv = std::clock();
  im1.convolute_opti(kernelY, kernelX);
  duration_classic_conv = (std::clock()- start_classic_conv)/(double)CLOCKS_PER_SEC;

  im1.display_Mat();
  im1.save_Mat("normal_conv.png");


  // Fourier convolution
  std::cout << "Demo convolution  in Fourier Space :" << std::endl ;
  Image im2(m_image2, m_name);
  std::clock_t start_fourier_conv;
  double duration_fourier_conv;
  start_fourier_conv = std::clock();
  cv::Mat convoluted = im2.fourier_convolution(kernel2);
  duration_fourier_conv = (std::clock()- start_fourier_conv)/(double)CLOCKS_PER_SEC;
  std::cout << "Duration of classic convolution : " << duration_classic_conv << '\n';
  std::cout << "Duration of fourier convolution : " << duration_fourier_conv << '\n';
  Image im_result(convoluted, "image_convoluted");

  im_result.display_Mat();
  im_result.save_Mat("dft_conv.png");

  // Difference between two results
  Image diff = im_result.Absolute_error_image(im1);
  diff.display_Mat();
  diff.save_Mat("diff_conv.png");

  return 0;
}
