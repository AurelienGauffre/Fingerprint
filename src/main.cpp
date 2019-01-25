#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "tests.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  cout << "*** Tests ***" << endl;
  // cout << "Test image :" << endl;
  // test_image(argv);

  // cout << "Test pressure :" << endl;
  // test_pressure(argv);

  // cout << "Test rotation :" << endl;
  // test_rotation(argv, M_PI/4, Pixel(128, 144));
  //
  // cout << "Test warp :" << endl;
  // test_warp(argv, M_PI/6, Pixel(110, 220), 50, 4);

  cout << "Test optimization :" << endl;
  test_optimization(argv);

  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0}  ;
  // std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1,-1}  ;
  // std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1}  ;
  // cout << "Test convolute" << endl ;
  // test_convolute_classic(argv,kernel);

  return 0;

}
