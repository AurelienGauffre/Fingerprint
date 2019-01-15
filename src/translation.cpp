#include <iostream>

#include "image.hpp"

void Image::translation_x(int p_x){
  std::vector<float> new_intensity_array;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      if (0 <= x - p_x < (int)m_width) {
        new_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(x-p_x,y)];
      } else {
        new_intensity_array[coord_to_index(x,y)] = 1;
      }
    }
  }
}

void Image::translation_y(int p_y){
  std::vector<float> new_intensity_array;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      if (0 <= y - p_y < (int)m_height) {
        new_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(x,y-p_y)];
      } else {
        new_intensity_array[coord_to_index(x,y)] = 1;
      }
    }
  }
}
