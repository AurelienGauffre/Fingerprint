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
#define attenuation_power 70

/*!
    *  \brief Application of a weight function (Exponential) on the pixels to keep just a circle of the fingerprint.
    *
    *  \param Coordinates of the circle center.
    */
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

/*!
    *  \fn float weight_exp(float coeff, unsigned int power, float r)
    *  \brief Exponential attenuation function.
    *
    *  \param Image : float : coefficient of attenuation, unsigned int : power, float : parameter.
    */
float weight_exp(float coeff, unsigned int power, float r){
  return std::exp(-std::pow(coeff*r,power));
}

/*!
    *  \brief Application of a weight function (Exponential) on the pixels to keep just an ellipse of the fingerprint.
    *
    *  \param percentage of variation of the ellipse size.
    */
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

/*!
    *  \brief Method to find the pixel of the image at the intersection between the row and the column with the max of intensity.
    *
    *  \return Pointer to the coordinates of the pixel found.
    */
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

/*!
    *  \brief Method to find the parameters of the ellipse that best represents the finger.
    *
    *  \return Pointer to the coordinates of the ellipse middle, its width and its height.
    */
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
