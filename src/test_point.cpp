#include <iostream>
#include "test_point.hpp"

using namespace std;

void test_point(char const *arg[]){
  string m_name = (string)arg[1];
  Mat m_image;
  m_image = imread(m_name, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(m_image, m_name);
  Point1 p1(0,1);
  cout << p1.find_pixel(im1) << endl;
  Point1 p2(258,im1);
  p2.display_coord();
}
