#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#include "image.hpp"

Image::Image(IplImage image):m_height(image.height),m_width(image.depth),m_size(image.height*image.width){
  m_pixels_array = new(float)[m_size];
  for (int i = 0; i < m_height; i++){
    for (int j = 0; j < m_width; j++){
      m_pixels_array[i*m_width + j] = (float)(cvPtr2D(&image, i, j,NULL)/255);
    }
  }
}
