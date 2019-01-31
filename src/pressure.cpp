/*!
    * \file pressure.cpp
    * \brief Set of methods and functions to simulate a variation of finger pressure during acquisition.
    *
    */
#include "pressure.hpp"

/*!
    *  \def attenuation_power
    *
    *  \brief Power of the exponential attenuation function which caracterizes the attenuation.
    */

//
#define attenuation_power 70


void Image::weight_coeff(int x_spot, int y_spot){
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      int diff_x = x - x_spot;
      int diff_y = y - y_spot;
      float r = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2));
      //64 is the radius of the circle we want to keep
      float c_r = weight_exp(1.0/64.0,attenuation_power,r);
      //new intensity = 1 - c*(1 - intensity) because 1 corresponds to white
      m_intensity_array[coord_to_index(x,y)] = 1 - c_r*(1-m_intensity_array[coord_to_index(x,y)]);
    }
  }
}


float weight_exp(float coeff, int power, float r){
  return std::exp(-std::pow(coeff*r,power));
}


void Image::weight_coeff_ellipse(float percentage){
  int *ellipse = this->find_ellipse();
  //We want to keep an ellipse of width percentage*ellipse_width
  float coeff = 1.0/(percentage*ellipse[2]);
  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      int diff_x = x - ellipse[0];
      int diff_y = y - ellipse[1];
      float a = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*std::pow((float)ellipse[2]/(float)ellipse[3],2));
      float c_r = weight_exp(coeff,attenuation_power,a);
      m_intensity_array[coord_to_index(x,y)] = 1 - c_r*(1-m_intensity_array[coord_to_index(x,y)]);
      //Apply sinus to add more white pixels
      m_intensity_array[coord_to_index(x,y)] = std::sin((M_PI/2)*m_intensity_array[coord_to_index(x,y)]);
    }
  }
  delete ellipse;
}

int *Image::find_max_intensity(){
  int res = new int[2]; // TO FIX Free somewhere but we may not need to use a dynamic allocation for these array
  float intensity_col_min = m_height;
  float intensity_row_min = m_width;
  for (int x = 0; x < m_width; x++) {
    float intensity_x = 0;
    for (int y = 0; y < m_height; y++) {
      intensity_x = intensity_x + m_intensity_array[coord_to_index(x,y)];
    }
    if (intensity_x < intensity_col_min) {
      intensity_col_min = intensity_x;
      res[0] = x;
    }
  }
  for (int y = 0; y < m_height; y++) {
    float intensity_y = 0;
    for (int x = 0; x < m_width; x++) {
      intensity_y = intensity_y + m_intensity_array[coord_to_index(x,y)];
    }
    if (intensity_y < intensity_row_min) {
      intensity_row_min = intensity_y;
      res[1] = y;
    }
  }
  return res;
}


int *Image::find_ellipse(){
  int *max_intensity = this->find_max_intensity();
  int nb_non_white_col = 0;
  for (int y = 0; y < m_height; y++) {
    if (m_intensity_array[coord_to_index(max_intensity[0],y)] != 1) {
      nb_non_white_col ++;
    }
  }
  int *res = new int[4]; // TO FIX
  res[0] = max_intensity[0]; //abscissa of the center
  res[1] = m_height - int(nb_non_white_col/2); //ordinate of the center
  //0.7 is approximately the quotient between the width and the height of a fingerprint
  res[2] = int(nb_non_white_col/2)*0.7; //width
  res[3] = int(nb_non_white_col/2); //height
  return res;
}
