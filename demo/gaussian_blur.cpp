#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

#include "tests.hpp"

int main(int argc, char const *argv[]) {
  cout << "Test convolution :" << endl ;
  dft_convolution(argv);
  return 0;
}
