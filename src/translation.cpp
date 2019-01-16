#include <iostream>

#include "image.hpp"

void Image::translation_x(int p_x){
  std::vector<float> new_intensity_array(m_size);
  for (unsigned int x = 0; x < m_width; x++) {
    for (unsigned int y = 0; y < m_height; y++) {
      int new_x = x - p_x;
      if ((0 <= new_x)  && (new_x < (int)m_width)) {
        new_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index((unsigned int)new_x,y)];
      } else {
        new_intensity_array[coord_to_index(x,y)] = 1;
      }
    }
  }
  m_intensity_array = new_intensity_array;
}

void Image::translation_y(int p_y){
  std::vector<float> new_intensity_array(m_size);
  for (unsigned int x = 0; x < m_width; x++) {
    for (unsigned int y = 0; y < m_height; y++) {
      int new_y = y - p_y;
      if ((0 <= new_y) && (new_y < (int)m_height)) {
        new_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(x,(unsigned int)new_y)];
      } else {
        new_intensity_array[coord_to_index(x,y)] = 1;
      }
    }
  }
  m_intensity_array = new_intensity_array;
}
