#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  cv::Mat m_image1;
  std::string m_name ;
  if (argc == 1){
    m_name = "../ressources/woman.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }


  m_image1 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  float sigma_clip = 6.0;
  for (int r = 1; r<=20; r++) {
    double sigma = (r/sigma_clip+0.5f);
    cv::Mat kX = cv::getGaussianKernel(2*r+1, sigma, CV_32F);
    cv::Mat kY = cv::getGaussianKernel(2*r+1, sigma, CV_32F);
    cv::Size opti_size = cv::Size(cv::getOptimalDFTSize(m_image1.cols), cv::getOptimalDFTSize(m_image1.rows));
    cv::Mat kernel2 = createFilterMask(opti_size, kX, kY); // Kernel used for convolution in Fourier Sapce

    std::vector<float> kernelX = Mat_to_vector(kX);
    std::vector<float> kernelY = Mat_to_vector(kY);

    // Usual convolution
    Image im0(m_image1, m_name);
    std::vector<float> kernel_full = Mat_to_vector(kX * kY.t());
    std::clock_t start_classic_conv;
    double duration_classic_conv;
    start_classic_conv = std::clock();
    im0.convolute_classic(kernel_full);
    duration_classic_conv = (std::clock()- start_classic_conv)/(double)CLOCKS_PER_SEC;

    // Usual convolution optimised
    Image im1(m_image1, m_name);
    std::clock_t start_opti_conv;
    double duration_opti_conv;
    start_opti_conv = std::clock();
    im1.convolute_opti(kernelY, kernelX);
    duration_opti_conv = (std::clock() - start_opti_conv)/(double)CLOCKS_PER_SEC;


    // Fourier convolution
    Image im2(m_image1, m_name);
    std::clock_t start_fourier_conv;
    double duration_fourier_conv;
    start_fourier_conv = std::clock();
    cv::Mat convoluted = im2.fourier_convolution(kernel2);
    duration_fourier_conv = (std::clock()- start_fourier_conv)/(double)CLOCKS_PER_SEC;
    std::cout << duration_classic_conv << ";"<< duration_opti_conv << ";" << duration_fourier_conv << '\n';
  }
  return 0;
}
