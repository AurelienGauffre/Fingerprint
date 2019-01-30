#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  std::string m_name = (std::string) argv[1];
  cv::Mat m_image;
  m_image = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image im1(m_image, m_name);
  // im1.display_attributes();
  // im1.display_Mat();
  // im1.save_Mat();
  // im1.save_Mat("other_name.png");
  // std::cout << im1.min_intensity() << im1.max_intensity() << std::endl;
  // int origine[2] = {30,0};
  // im1.draw_rectangle(1,origine,30,300);
  // im1.draw_rectangle(0,origine,10,10);
  // im1.display_Mat();
  // im1.symetry_y();
  // im1.display_Mat();
  // im1.symetry_diag();
  //

  Image im2(im1);
  int origine[2] = {30,0};
  im1.draw_rectangle(1,origine,30,300);
  im2.display_Mat();
  im1.display_Mat();
  // im1.data_intensity();
  return 0;

}
