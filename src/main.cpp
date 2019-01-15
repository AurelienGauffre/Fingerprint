#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "tests.hpp"

int main(int argc, char const *argv[]) {
  cout << "Test image :" << endl;
  test_image(argv);
  cout << "Test pressure :" << endl;
  test_pressure(argv);
  cout << "Test rotation :" << endl;
  test_rotation(argv, M_PI/4, Pixel(128, 128));
  cout << "Test optimization :" << endl;
  test_optimization(argv);
  return 0;

}
