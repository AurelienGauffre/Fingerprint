#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include "image.hpp"

int main(int argc, char const *argv[]) {
  const char* m_image = argv[1];
  Mat image;
  image = imread(m_image, CV_LOAD_IMAGE_GRAYSCALE);
  Image im1(image);

  // if( argc != 2 || !image.data )
  // {
  //   cout << "No image data" << endl;
  //   return -1;
  // }

  im1.display();
  im1.back_to_Mat();
  cv::imwrite("result.png",*im1.get_original());
  // namedWindow("result.png", WINDOW_AUTOSIZE);
  // imshow("result.png", im1);
  // waitKey(0);

  return 0;
}
