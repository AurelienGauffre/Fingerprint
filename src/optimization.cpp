#include <iostream>

#include "image.hpp"

int Image::optimization(Image &modele){
  std::vector<int> list_px;
  for (int k = -m_width + 1; k < (int)m_width; k++) {
    list_px.push_back(k);
  }
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      std::vector<float> list_l;
      std::vector<int> list_p;
      std::vector<int> new_list_px;
      for (unsigned int k = 0; k < list_px.size(); k++){
        int new_x = x + list_px[k];
        if (0 <= new_x && new_x < (int)m_width) {
          float diff = modele.get_intensity(coord_to_index(new_x,y)) - m_intensity_array[coord_to_index(x,y)];
          float l = std::pow(diff,2);
          list_l.push_back(l);
          list_p.push_back(list_px[k]);
        } else {
          new_list_px.push_back(list_px[k]);
        }
      }
      float l_min;
      if (list_l.size() != 0) {
        l_min = *std::min_element(list_l.begin(),list_l.end());
      }
      for (unsigned int k = 0; k < list_l.size(); k++) {
        if (list_l[k] == l_min) {
          new_list_px.push_back(list_p[k]);
        }
      }
      list_px = new_list_px;
    }
  }
  return list_px[0];
}
