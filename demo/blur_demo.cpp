#include "linear_filter.hpp"

int main(int argc, char const *argv[]) {
  cv::Mat m_ref = cv::imread("../ressources/Rotation4/5.png", cv::IMREAD_GRAYSCALE);
  cv::Mat m_image1;
  std::string m_name;
  if (argc == 1){
    m_name = "../ressources/Rotation4/5.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }
  m_image1 = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  assert(m_image1.size() == m_ref.size() && "We need the input image to have the same size\
  than our noised image from Photoshop. Try with images comming directly from Regis' sensor.");
  Image im1(m_image1, m_name);
  im1.convolute_blur(5,5); // convolute blur(kernel_radius,speed)
  im1.save_Mat();
  im1.display_Mat();
  return 0;
}
