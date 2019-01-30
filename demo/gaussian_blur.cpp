#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

#include "tests.hpp"

int main(int argc, char const *argv[]) {
  //cout << "Test convolution :" << endl ;
  // test_inv_ft(argv);


  //std::vector<float> kernel = {0,0,0,0,1,0,0,0,0};
  //std::vector<float> kernel = {1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0,1/9.0}  ;
  //std::vector<float> kernel = {-1,-1,-1,-1,9,-1,-1,-1,-1,-1}  ;
  //std::vector<float> kernel = {-1,0,1,-2,0,2,-1,0,1}  ;

  // std::vector<float> kernel_col =  {1,2,4,2,1};
  // std::vector<float> kernel_line = {1,2,4,2,1};

  std::vector<float> kernel_col =  {1,2,1};
  std::vector<float> kernel_line = {-1,0,1};

  cout << "Test convolution :" << endl;
  //test_convolute_classic(argv,kernel);
  test_convolute_blur(50,1,1);


  return 0;
}
