#include <iostream>

#include "image.hpp"

void Image::translation(float p_x,float p_y){
  std::vector<Pixel> pixels(this->convert_to_pixels());
  std::vector<Pixel> former_pixels(this->translate_pixels(pixels, -p_x, -p_y));
  this->bilinear_interpolation(former_pixels);
}

std::vector<Pixel> Image::translate_pixels(std::vector<Pixel>& Pixel_array, float p_x, float p_y) {
  std::vector<Pixel> Pixel_array_translated;
  for (unsigned int i = 0; i < Pixel_array.size(); i++) {
    Pixel_array_translated.push_back(Pixel_array[i].translation_one_pixel(p_x,p_y));
  }
  return Pixel_array_translated;
}
