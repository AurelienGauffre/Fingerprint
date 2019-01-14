#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "image.hpp"
#include "test_image.hpp"

int main(int argc, char const *argv[]) {
  cout << "Test image :" << endl;
  test_rotation(argv, M_PI/4*0, Pixel(128, 128));
  //Pixel p(1,0,1);
  // p=p.rotation(Pixel(0,0),M_PI/4);
  // cout << '('<< p.get_x() <<','<<p.get_y()<<')'<< endl ;
  return 0;

}
