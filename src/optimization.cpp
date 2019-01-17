#include "optimization.hpp"


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

Image Image::Absolute_error_image(Image &modele, std::vector<float> p){
  Image res = Image(*m_original_image, m_name.substr(0, m_name.size()-4) + "_error.png");
  this->translation(p[0],p[1]);
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      *res.get_pointer(coord_to_index(x,y)) = std::abs(m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y)));
    }
  }
  return res;
}

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
  return this->covariance(modele)/sqrt(modele.covariance(modele)*this->covariance(*this));
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

float Image::covariance(Image &other){
  float sum = 0;
  float mean1 = this->mean();
  float mean2 = other.mean();
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      sum += (m_intensity_array[coord_to_index(x,y)] - mean1)*(other.get_intensity(coord_to_index(x,y)) - mean2);
    }
  }
  return sum;
}

unsigned int optimize(std::vector<float> list_l, bool max){
  float l_opt = list_l[0];
  unsigned int index = 0;
  while (std::isnan(std::abs(l_opt))){
    index++;
    l_opt = list_l[index];
  }
  for (unsigned int k = index+1; k < list_l.size(); k++){
    if (max) {
      if (list_l[k] < l_opt){
        l_opt = list_l[k];
        index = k;
      }
    } else {
      if ((std::abs(list_l[k]) > l_opt) && !std::isnan(std::abs(list_l[k]))){
        l_opt = std::abs(list_l[k]);
        index = k;
      }
    }
  }
  return index;
}


std::vector<float> Image::opti_complex(Image &modele, bool squarred){
  std::vector<int> list_px;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = -m_width + 1; k < (int)m_width; k++) {
    list_px.push_back(k);
  }
  for (unsigned int k = 0; k < list_px.size(); k++) {
    this->translation(list_px[k],0);
    if (squarred){
      list_l.push_back(this->squared_error(modele));
    } else {
      list_l.push_back(this->correlation(modele));
    }
    m_intensity_array= copy_intensity_array;
  }
  unsigned int index = optimize(list_l,squarred);
  std::cout << "\n" << list_px[index];
  std::vector<float> p(1);
  p[0] = list_px[index];
  return p;
}

std::vector<float> Image::opti_complex_xy(Image &modele, bool squarred){
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
      this->translation(list_px[i],list_py[j]);
      if (squarred){
        list_l.push_back(this->squared_error(modele));
      } else {
        list_l.push_back(this->correlation(modele));
      }
      m_intensity_array= copy_intensity_array;
    }
  }
  unsigned int index = optimize(list_l,squarred);
  std::vector<float> p(2);
  // std::cout << " 0 " << list_px[index/list_py.size()] << " 1 "  <<list_py[index%list_py.size()] << std::endl;
  p[0] = list_px[index/list_py.size()];
  p[1] = list_py[index%list_py.size()];
  return p;
}

std::vector<float> Image::opti_subpixel(Image &modele, bool squarred){
  std::vector<float> p = this->opti_complex_xy(modele,squarred);
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  float px = p[0];
  float py = p[1];
  float l;
  float l_g;
  float l_d;
  this->translation(px,py);
  if (squarred){
    l = this->squared_error(modele);
  } else {
    l = 1 - std::abs(this->correlation(modele));
  }
  m_intensity_array= copy_intensity_array;
  float px_g;
  float px_d;
  float distance = 0.5;
  while (distance > 0.06){
    px_g = px - distance;
    px_d = px + distance;
    if (squarred){
      this->translation(px_g,py);
      l_g = this->squared_error(modele);
      m_intensity_array= copy_intensity_array;
      this->translation(px_d,py);
      l_d = this->squared_error(modele);
      m_intensity_array= copy_intensity_array;
    } else {
      this->translation(px_g,py);
      l_g = 1 - std::abs(this->correlation(modele));
      m_intensity_array = copy_intensity_array;
      this->translation(px_d,py);
      l_d = this->correlation(modele);
      m_intensity_array= copy_intensity_array;
    }
    if (l_d < l_g) {
      l = l_d;
      px = px_d;
    } else {
      l = l_g;
      px = px_g;
    }
    distance = distance/2.0;
  }
  this->translation(px,py);
  if (squarred){
    l = this->squared_error(modele);
  } else {
    l = 1 - std::abs(this->correlation(modele));
  }
  m_intensity_array= copy_intensity_array;
  float py_g;
  float py_d;
  distance = 0.5;
  while (distance > 0.06){
    py_g = py - distance;
    py_d = py + distance;
    if (squarred){
      this->translation(px,py_g);
      l_g = this->squared_error(modele);
      m_intensity_array= copy_intensity_array;
      this->translation(px,py_d);
      l_d = this->squared_error(modele);
      m_intensity_array= copy_intensity_array;
    } else {
      this->translation(px,py_g);
      l_g = 1 - std::abs(this->correlation(modele));
      m_intensity_array = copy_intensity_array;
      this->translation(px,py_d);
      l_d = this->correlation(modele);
      m_intensity_array= copy_intensity_array;
    }
    if (l_d < l_g) {
      l = l_d;
      py = py_d;
    } else {
      l = l_g;
      py = py_g;
    }
    distance = distance/2.0;
  }
  std::vector<float> res(2);
  res[0] = px;
  res[1] = py;
  return res;
}
