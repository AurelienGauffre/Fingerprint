#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Image {
  private:
    float *m_pixels_array;
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
  public:
    Image(IplImage image);
}
