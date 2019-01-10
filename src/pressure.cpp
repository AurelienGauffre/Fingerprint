#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>
#include <cmath>

#include "pressure.hpp"

void Image::weight_coeff(unsigned int x_spot, unsigned int y_spot){
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      int diff_x = x - x_spot;
      int diff_y = y - y_spot;
      float r = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2));
      float c_r = weight_exp(1.0/100.0,100,r);
      m_pixels_array[coord_to_index(x,y)] = 1 - c_r*(1-m_pixels_array[coord_to_index(x,y)]);
    }
  }
}

float weight_exp(float coeff, unsigned int power, float r){
  return std::exp(-std::pow(coeff*r,power));
}

float weight_inv(float coeff, unsigned int power, float r){
  return 1/(1 + std::pow(coeff*r,power));
}

// void Image::weight_coeff_ellipse(unsigned int x_spot, unsigned int y_spot){
//   for (unsigned int y = 0; y < m_height; y++) {
//     for (unsigned int x = 0; x < m_width; x++) {
//       int diff_x = x - x_spot;
//       int diff_y = y - y_spot;
//       float r = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2));
//       float c_r = weight_exp(1.0/100.0,100,r);
//       m_pixels_array[coord_to_index(x,y)] = 1 - c_r*(1-m_pixels_array[coord_to_index(x,y)]);
//     }
//   }
// }
