#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class Image {
  private:
    vector<float> m_pixels_array;
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    Mat *m_original_image;
  public:
    Image(Mat image);
    void display();
    void back_to_Mat();
    Mat *get_original();
};
