/*!
 * \file image.cpp
 * \brief Definition of image class methods
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 01/08/2019
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>

using namespace cv;
using namespace std;

#include "image.hpp"

/*!
     *  \brief Basic Image constructor
     *
     *  Constructor of class Image 
     *
     *  \param listSongs : image "Mat", name
     */
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
  m_original_image->rows = m_height;
  m_original_image->cols = m_width;
  cout << m_original_image->size()<< endl ;
  //resize(*m_original_image,*m_original_image,Size(m_height,m_width));
  for (unsigned int y = 0; y < m_height; y++){
    for (unsigned int x = 0; x < m_width; x++){
      m_original_image->ptr<uchar>(y)[x] = (uchar)(255*m_pixels_array[coord_to_index(x,y)]);
    }
  }
}

Mat *Image::get_original(){
  return m_original_image;
}

void Image::display_Mat(){
  this->back_to_Mat();
  namedWindow("result.png", 100000);
  imshow("result.png", *m_original_image);
  waitKey(0);
}

void Image::save_Mat(string name){
  this->back_to_Mat();
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

unsigned int Image::coord_to_index(unsigned int x, unsigned int y){
  return y*m_width + x;
}
unsigned int *Image::index_to_coord(unsigned int k){
  unsigned int *result = new unsigned int[2];
  result[0] = k%m_width;
  result[1] = k/m_width;
  return result;
}

void Image::draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height){
  unsigned int x_min = origine[0]; //raise error
  unsigned int y_min = origine[1];
  unsigned int x_max = min(x_min + width-1,m_width-1);
  unsigned int y_max = min(y_min + height-1,m_height-1);
  for (unsigned int x = x_min; x <= x_max; x++) {
    for (unsigned int y = y_min; y <= y_max; y++) {
      m_pixels_array[coord_to_index(x,y)] = intensity;
    }
  }
}

void Image::symetry_y(){
  for (unsigned int y = 0; y < m_height; y++){
    for (unsigned int x= 0; x < m_width/2; x++){
      float tmp = m_pixels_array[coord_to_index(x,y)];
      m_pixels_array[coord_to_index(x,y)] = m_pixels_array[coord_to_index(m_width -1 - x,y)];
      m_pixels_array[coord_to_index(m_width -1 - x,y)] = tmp;
    }
  }
}

void Image::symetry_diag(){

  vector<float> m_new_pixels_array;
  for (unsigned int x = 0; x < m_width; x++){
    for (unsigned int y= 0; y < m_height; y++){
      m_new_pixels_array.push_back(m_pixels_array[coord_to_index(x,y)]);

      // float tmp2 = m_pixels_array[coord_to_index(x,y)];
      // m_pixels_array[coord_to_index(x,y)] = m_pixels_array[coord_to_index(y,x)];
      // m_pixels_array[coord_to_index(y,x)] = tmp2;
    }
  }
  m_pixels_array = m_new_pixels_array ;
  unsigned int tmp1 = m_width;
  m_width = m_height;
  m_height = tmp1;
}
