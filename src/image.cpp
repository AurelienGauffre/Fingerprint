#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>

using namespace cv;
using namespace std;

#include "image.hpp"

Image::Image(Mat image, string name){
  char s = '/';
  int pos = 0;
  for (int k = name.size() - 1; (name[k] != s)&&(k>-1); k--){
    pos = k;
  }
  if (pos == -1){
    m_name = name;
  } else {
    m_name = name.substr(pos,name.size()-pos);
  }
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

void Image::display_attributes(){
  for (unsigned int k = 0 ; k < m_size; k++){
    cout << m_pixels_array[k] << " ";
  }
  cout << m_height << " " << m_width << " " << m_size << "" << m_name << endl;
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

void Image::display_Mat(){
  namedWindow("result.png", WINDOW_AUTOSIZE);
  imshow("result.png", *m_original_image);
  waitKey(0);
}

void Image::save_Mat(string name){
  if (name == ""){
    name ="result_" + m_name;
  }
  cv::imwrite(name,*m_original_image);
}

float Image::min_intensity(){
  return *min_element(m_pixels_array.begin(),m_pixels_array.end());
}
float Image::max_intensity(){
  return *max_element(m_pixels_array.begin(),m_pixels_array.end());
}

unsigned int Image::get_width(){
  return m_width;
}
