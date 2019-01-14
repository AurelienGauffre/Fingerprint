#include <iostream>
#include <cmath>
#include <math.h>

#include "pressure.hpp"

#define attenuation_power 70

void Image::weight_coeff(unsigned int x_spot, unsigned int y_spot){
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      int diff_x = x - x_spot;
      int diff_y = y - y_spot;
      float r = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2));
      float c_r = weight_exp(1.0/64.0,attenuation_power,r);
      m_intensity_array[coord_to_index(x,y)] = 1 - c_r*(1-m_intensity_array[coord_to_index(x,y)]);
    }
  }
}

float weight_exp(float coeff, unsigned int power, float r){
  return std::exp(-std::pow(coeff*r,power));
}

void Image::weight_coeff_ellipse(float percentage){
  unsigned int *ellipse = this->find_ellipse();
  float coeff = 1.0/(percentage*ellipse[2]);
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      int diff_x = x - ellipse[0];
      int diff_y = y - ellipse[1];
      float a = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*std::pow((float)ellipse[2]/(float)ellipse[3],2));
      float c_r = weight_exp(coeff,attenuation_power,a);
      m_intensity_array[coord_to_index(x,y)] = 1 - c_r*(1-m_intensity_array[coord_to_index(x,y)]);
      m_intensity_array[coord_to_index(x,y)] = std::sin((M_PI/2)*m_intensity_array[coord_to_index(x,y)]);
    }
  }
  delete ellipse;
}

unsigned int *Image::find_ellipse(){
  float percentage_col_min = m_height;
  unsigned int col_min = 0;
  for (unsigned int x = 0; x < m_width; x++) {
    float percentage = 0;
    for (unsigned int y = 0; y < m_height; y++) {
      percentage = percentage + m_intensity_array[coord_to_index(x,y)];
    }
    if (percentage < percentage_col_min) {
      percentage_col_min = percentage;
      col_min = x;
    }
  }
  unsigned int nb_non_white_col = 0;
  for (unsigned int y = 0; y < m_height; y++) {
    if (m_intensity_array[coord_to_index(col_min,y)] != 1) {
      nb_non_white_col ++;
    }
  }
  unsigned int *res = new unsigned int[4];
  res[0] = col_min;
  res[1] = m_height - int(nb_non_white_col/2);
  res[2] = int(nb_non_white_col/2)*0.7;
  res[3] = int(nb_non_white_col/2);
  return res;
}
