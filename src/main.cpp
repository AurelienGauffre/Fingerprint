#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace cv;
using namespace std;

#include "image.hpp"

#include "test_image.hpp"

int main(int argc, char const *argv[]) {
  cout << "Test image :" << endl;
  test_image(argv);
  return 0;
}
