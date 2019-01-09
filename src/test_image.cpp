#include <iostream>
#include <opencv2/opencv.hpp>
#include "test_image.hpp"

using namespace std;

void test_image(char const *arg[]){
  string m_name = (string)arg[1];
  Mat m_image;
  m_image = imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);
  //im1.display_attributes();
  im1.back_to_Mat();
  im1.display_Mat();
  im1.save_Mat();
  im1.save_Mat("other_name.png");
  cout << im1.min_intensity() << im1.max_intensity();
}
