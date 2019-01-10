#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "test_image.hpp"
#include "test_pressure.hpp"

int main(int argc, char const *argv[]) {
  cout << "Test image :" << endl;
  test_image(argv);
  cout << "Test pressure :" << endl;
  test_pressure(argv);
  return 0;
}
