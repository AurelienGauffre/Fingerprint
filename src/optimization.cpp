#include <iostream>
#include <fstream>

#include "image.hpp"


// int Image::optimization(Image &modele){
//   std::vector<int> list_px;
//   for (int k = -m_width + 1; k < (int)m_width; k++) {
//     list_px.push_back(k);
//   }
//   for (int y = 0; y < (int)m_height; y++) {
//     for (int x = 0; x < (int)m_width; x++) {
//       std::vector<float> list_l;
//       std::vector<int> list_p;
//       std::vector<int> new_list_px;
//       for (unsigned int k = 0; k < list_px.size(); k++){
//         int new_x = x + list_px[k];
//         if (0 <= new_x && new_x < (int)m_width) {
//           float diff = modele.get_intensity(coord_to_index(new_x,y)) - m_intensity_array[coord_to_index(x,y)];
//           float l = std::pow(diff,2);
//           list_l.push_back(l);
//           list_p.push_back(list_px[k]);
//         } else {
//           int new_new_x = m_width - x;
//           float diff = modele.get_intensity(coord_to_index(new_new_x,y)) - 1.0;
//           if (diff == 0){
//             new_list_px.push_back(list_px[k]);
//           }
//         }
//       }
//       float l_min;
//       if (list_l.size() != 0) {
//         l_min = *std::min_element(list_l.begin(),list_l.end());
//       }
//       for (unsigned int k = 0; k < list_l.size(); k++) {
//         if (list_l[k] == l_min) {
//           new_list_px.push_back(list_p[k]);
//         }
//       }
//       list_px = new_list_px;
//     }
//   }
//   return list_px[0];
// }

float Image::squared_error(Image &modele){
  float sum = 0;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      float diff = m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y));
      sum += std::pow(diff,2);
    }
  }
  return sum;
}

float Image::correlation(Image &modele){
  float sum = 0;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      float diff = m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y));
      sum += std::pow(diff,2);
    }
  }
  return sum;
}

float Image::mean(){
  float sum = 0;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      sum += m_intensity_array[coord_to_index(x,y)];
    }
  }
  return sum/m_size;
}

float Image::diff_mean(){
  float sum = 0;
  float mean = this->mean();
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      sum += (m_intensity_array[coord_to_index(x,y)] - mean);
    }
  }
  return sum;
}

int Image::opti_complex(Image &modele){
  std::vector<int> list_px;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = -m_width + 1; k < (int)m_width; k++) {
    list_px.push_back(k);
  }
  for (unsigned int k = 0; k < list_px.size(); k++) {
    this->translation_x(list_px[k]);
    list_l.push_back(this->squared_error(modele));
    m_intensity_array= copy_intensity_array;
  }
  float l_min = list_l[0];
  unsigned int index = 0;
  for (unsigned int k = 1; k < list_l.size(); k++){
    if (list_l[k] < l_min){
      l_min = list_l[k];
      index = k;
    }
  }
  return list_px[index];
}

int Image::opti_complex_xy(Image &modele){
  std::vector<int> list_px;
  std::vector<int> list_py;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = -m_width + 1; k < (int)m_width; k++) {
    list_px.push_back(k);
  }
  for (int k = -m_height + 1; k < (int)m_height; k++) {
    list_py.push_back(k);
  }
  for (unsigned int i = 0; i < list_px.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      this->translation_x(list_px[i]);
      this->translation_y(list_py[j]);
      float l = 0.0;
      for (int x = 0; x < (int)m_width; x++) {
        for (int y = 0; y < (int)m_height; y++) {
          float diff = modele.get_intensity(coord_to_index(x,y)) - m_intensity_array[coord_to_index(x,y)];
          l += std::pow(diff,2);
        }
      }
      list_l.push_back(l);
      m_intensity_array= copy_intensity_array;
    }
  }
  float l_min = list_l[0];
  unsigned int index = 0;
  for (unsigned int k = 1; k < list_l.size(); k++){
    if (list_l[k] < l_min){
      l_min = list_l[k];
      index = k;
    }
  }

  int px = list_px[index/list_py.size()];
  int py = list_py[index%list_py.size()];
  std::cout << px << " ";
  return py;
}
