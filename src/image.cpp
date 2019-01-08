#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

#include "image.hpp"

Image::Image(Mat image){
  IplImage tmp = image;
  m_height = tmp.height;
  m_width = tmp.depth;
  m_size = m_width*m_height;
  for (unsigned int i = 0; i < m_height; i++){
    for (unsigned int j = 0; j < m_width; j++){
      m_pixels_array.push_back(((int)(*cvPtr2D(&tmp, i, j,NULL)))/255);
    }
  }
}

Mat Image::Back_to_Mat(Image image){
  
  return ;
}
