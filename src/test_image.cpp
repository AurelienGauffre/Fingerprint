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
  cout << "test rectangle :" << endl;
  unsigned int *origine = new unsigned int[2];
  origine[0] = 0;
  origine[1] = 0;
  im1.draw_rectangle(1,origine,1,5);
  im1.draw_rectangle(0,origine,1,1);
  im1.back_to_Mat();
  im1.display_Mat();

}
