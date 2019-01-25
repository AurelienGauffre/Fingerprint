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
      m_intensity_array[coord_to_index(x,y)] = std::sin((M_PI/2)*m_intensity_array[coord_to_index(x,y)]); // FIX sin pas bon. utiliser sqrt
    }
  }
  delete ellipse;
}

unsigned int *Image::find_max_intensity(){
  unsigned int *res = new unsigned int[2];
  float intensity_col_min = m_height;
  float intensity_row_min = m_width;
  for (unsigned int x = 0; x < m_width; x++) {
    float intensity_x = 0;
    for (unsigned int y = 0; y < m_height; y++) {
      intensity_x = intensity_x + m_intensity_array[coord_to_index(x,y)];
    }
    if (intensity_x < intensity_col_min) {
      intensity_col_min = intensity_x;
      res[0] = x;
    }
  }
  for (unsigned int y = 0; y < m_height; y++) {
    float intensity_y = 0;
    for (unsigned int x = 0; x < m_width; x++) {
      intensity_y = intensity_y + m_intensity_array[coord_to_index(x,y)];
    }
    if (intensity_y < intensity_row_min) {
      intensity_row_min = intensity_y;
      res[1] = y;
    }
  }
  return res;
}

unsigned int *Image::find_ellipse(){
  unsigned int *max_intensity = this->find_max_intensity();
  unsigned int nb_non_white_col = 0;
  for (unsigned int y = 0; y < m_height; y++) {
    if (m_intensity_array[coord_to_index(max_intensity[0],y)] != 1) {
      nb_non_white_col ++;
    }
  }
  unsigned int *res = new unsigned int[4];
  res[0] = max_intensity[0];
  res[1] = m_height - int(nb_non_white_col/2);
  res[2] = int(nb_non_white_col/2)*0.7;
  res[3] = int(nb_non_white_col/2);
  return res;
}
