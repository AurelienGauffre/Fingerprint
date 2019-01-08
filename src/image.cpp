#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>

using namespace cv;
using namespace std;

#include "image.hpp"

Image::Image(Mat image){
  m_height = image.rows;
  m_width = image.cols;
  m_size = m_width*m_height;
  m_original_image = new(Mat);
  *m_original_image = image;
  for (unsigned int i = 0; i < m_height; i++){
    for (unsigned int j = 0; j < m_width; j++){
      m_pixels_array.push_back(((int)(image.at<uchar>(i, j)))/255.0);
    }
  }
}

void Image::display(){
  for (int k = 0 ; k < m_size; k++){
    cout << m_pixels_array[k] << " ";
  }
  cout << m_height << " " << m_width << " " << m_size << endl;
}

void Image::back_to_Mat(){
  for (unsigned int i = 0; i < m_height; i++){
    for (unsigned int j = 0; j < m_width; j++){
      m_original_image->ptr<uchar>(i)[j] = (uchar)(255*m_pixels_array[i*m_width + j]);
    }
  }
}

Mat *Image::get_original(){
  return m_original_image;
}
