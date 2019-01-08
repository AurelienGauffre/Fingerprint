#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[]) {
  const char* m_image = argv[1];
  Mat image;
  image = imread(m_image, CV_LOAD_IMAGE_GRAYSCALE);
  IplImage tmp = image;
  uchar* p;
  p = cvPtr2D(&tmp, 128, 70,NULL);
  int a = (int)(*p);
  cout << a << endl;
  if( argc != 2 || !image.data )
  {
    cout << "No image data" << endl;
    return -1;
  }
  namedWindow(m_image, WINDOW_AUTOSIZE);
  imshow(m_image, image);
  waitKey(0);
  return 0;
}
