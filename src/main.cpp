#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "tests.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  cout << "*** Tests ***" << endl;
  test_image(argv);

  // cout << "Test pressure :" << endl;
  // test_pressure(argv);

  // cout << "Test rotation :" << endl;
  // test_rotation(argv, M_PI/4, Pixel(128, 128));
  //
  // cout << "Test warp :" << endl;
  // test_warp(argv, M_PI/6, Pixel(110, 220), 50, 4);


  //cout << "Test optimization :" << endl;
  //test_optimization(argv);
  std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1}  ;
  cout << "Test convolute" << endl ;
  test_convolute(argv,kernel);
  return 0;

}
