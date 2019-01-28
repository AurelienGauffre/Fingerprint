/*!
    * \file translation.cpp
    * \brief Set of methods to translate the image along the x and y axis.
    *
    */
#include "image.hpp"

/*!
    *  \brief Translates the image using translate_pixels and bilinear_interpolation.
    *
    *  \param floats parameters p_x and p_y of translation.
    */
void Image::translation(float p_x,float p_y){
  std::vector<Pixel> pixels(this->convert_to_pixels());
  std::vector<Pixel> former_pixels(this->translate_pixels(pixels, -p_x, -p_y));
  this->bilinear_interpolation(former_pixels);
}

/*!
    *  \brief Translates the pixel array of p_x along the x axis and of p_y along the y axis.
    *
    *  \param vector of the image pixels, floats parameters p_x and p_y of translation.
    */
std::vector<Pixel> Image::translate_pixels(std::vector<Pixel>& Pixel_array, float p_x, float p_y) {
  std::vector<Pixel> Pixel_array_translated;
  for (unsigned int i = 0; i < Pixel_array.size(); i++) {
    Pixel_array_translated.push_back(Pixel_array[i].translation_one_pixel(p_x,p_y));
  }
  return Pixel_array_translated;
}
