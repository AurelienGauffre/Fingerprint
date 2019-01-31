/*!
    * \file optimization.cpp
    * \brief Set of optimization methods and function.
    *
    * Methods and function of optimization of the differents parameters of translation and rotation of the image.
    *
    */

#include "optimization.hpp"


Image Image::Absolute_error_image(Image &modele){
  Image res = Image(*m_original_image, m_name.substr(0, m_name.size()-4) + "_error.png");
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      *res.get_pointer(coord_to_index(x,y)) = std::abs(m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y)));
    }
  }
  return res;
}


float Image::squared_error(Image &modele){
  assert(m_original_image->size() == modele.get_original_image()->size());
  float sum = 0;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      float diff = m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y));
      sum += std::pow(diff,2);
    }
  }
  return sum;
}

float Image::error_rate(Image &modele){
  assert(m_original_image->size() == modele.get_original_image()->size());
  float sum = 0;
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      float diff = std::abs(m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y)));
      sum += diff;
    }
  }
  return sum/(m_width*m_height);
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
  return sum/(float)m_size;
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


int optimize(std::vector<float> list_l, bool squared){
  float l_opt = list_l[0];
  int index = 0;
  //Go to the first value that is not nan
  while (std::isnan(std::abs(l_opt))){
    index++;
    l_opt = list_l[index];
  }
  for (unsigned int k = index+1; k < list_l.size(); k++){
    //Minimize
    if (squared) {
      if (list_l[k] < l_opt){
        l_opt = list_l[k];
        index = k;
      }
    //Maximize
    } else {
      if ((std::abs(list_l[k]) > l_opt) && !std::isnan(std::abs(list_l[k]))){
        l_opt = std::abs(list_l[k]);
        index = k;
      }
    }
  }
  return index;
}


float Image::opti_greedy_x_aux(float &px, Image &modele, bool squared, bool plot) {
  this->opti_greedy_x(px, modele, squared, plot);
  return px;
}


void Image::opti_greedy_x(float &px, Image &modele, bool squared, bool plot){
  std::ofstream fichier;
  if (plot == true) {
    std::string nom_fichier = "../results/data_opti_greedy_fast_x_" + m_name + ".txt";
    fichier.open(nom_fichier.c_str(), std::ios::out);
    if (fichier.fail()) {
      std::cerr << " Impossible d'ouvrir le fichier ! " << std::endl;
    }
  }
  std::vector<int> list_px;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = (int)((int)(-m_width)/2); k < (int)(m_width/2); k++) {
    list_px.push_back(k);
  }
  for (unsigned int k = 0; k < list_px.size(); k++) {
    float l = this->compute_l_xy(modele, list_px[k], 0, squared, copy_intensity_array);
    list_l.push_back(l);
    if (plot == true) {
      fichier << list_px[k] << " " << l << std::endl;
    }
  }
  if (plot){
    fichier.close();
  }
  int index = optimize(list_l,squared);
  px = list_px[index];
}


void Image::opti_greedy_xy(float p[2], Image &modele, bool squared){
  std::vector<int> list_px;
  std::vector<int> list_py;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = (int)((int)(-m_width)/2); k < (int)(m_width/2); k++) {
    list_px.push_back(k);
  }
  for (int k = (int)((int)(-m_height)/2); k < (int)(m_height/2); k++) {
    list_py.push_back(k);
  }
  for (unsigned int i = 0; i < list_px.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      float l = this->compute_l_xy(modele, list_px[i], list_py[j], squared, copy_intensity_array);
      list_l.push_back(l);
    }
  }
  int index = optimize(list_l,squared);
  p[0] = list_px[index/list_py.size()];
  p[1] = list_py[index%list_py.size()];
}


float Image::compute_l_xy(Image &modele, float px, float py, bool squared, std::vector<float> &copy_intensity_array){
  float l;
  if (squared){
    this->translation(px,py);
    l = this->squared_error(modele);
    m_intensity_array= copy_intensity_array;
  } else {
    this->translation(px,py);
    l = this->correlation(modele);
    m_intensity_array= copy_intensity_array;
  }
  return l;
}


float Image::compute_l_rxy(Image &modele, float px, float py, float angle, bool squared, std::vector<float> &copy_intensity_array){
  float l;
  if (squared){
    this->translation(px,py);
    this->rotate_bilinear(angle, Pixel(m_width/2, m_height/2, 0));
    l = this->squared_error(modele);
    m_intensity_array= copy_intensity_array;
  } else {
    this->translation(px,py);
    this->rotate_bilinear(angle, Pixel(m_width/2, m_height/2, 0));
    l = this->correlation(modele);
    m_intensity_array= copy_intensity_array;
  }
  return l;
}


void Image::opti_subpixel(float p[2], Image &modele, bool squared){
  this->opti_greedy_fast_xy(p, modele, squared, false);
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  float px = p[0];
  float py = p[1];
  float l_g, l_d, px_g, px_d, py_g, py_d;
  float distance = 0.5;
  //Find the best p_x
  while (distance > 0.06){
    px_g = px - distance;
    px_d = px + distance;
    l_g = compute_l_xy(modele,px_g,py,squared,copy_intensity_array);
    l_d = compute_l_xy(modele,px_d,py,squared,copy_intensity_array);
    if (l_d < l_g) {
      px = px_d;
    } else {
      px = px_g;
    }
    distance = distance/2.0;
  }
  distance = 0.5;
  //Find the best p_y
  while (distance > 0.06){
    py_g = py - distance;
    py_d = py + distance;
    l_g = compute_l_xy(modele,px,py_g,squared,copy_intensity_array);
    l_d = compute_l_xy(modele,px,py_d,squared,copy_intensity_array);
    if (l_d < l_g) {
      py = py_d;
    } else {
      py = py_g;
    }
    distance = distance/2.0;
  }
  p[0] = px;
  p[1] = py;
}


void Image::opti_greedy_fast_xy(float p[2], Image &modele, bool squared, bool plot){
  std::ofstream fichier;
  if (plot == true) {
    std::string nom_fichier = "../results/data_opti_greedy_fast_xy_" + m_name + ".txt";
    fichier.open(nom_fichier.c_str(), std::ios::out);
    if (fichier.fail()) {
      std::cerr << " Impossible d'ouvrir le fichier ! " << std::endl;
    }
  }
  int *max_intensity1 = this->find_max_intensity();
  int *max_intensity2 = modele.find_max_intensity();
  std::cout << max_intensity1[0] << " " << max_intensity1[1] << " " << max_intensity2[0] << " " << max_intensity2[1] << std::endl;
  int diff_x = max_intensity2[0] - max_intensity1[0];
  int diff_y = max_intensity2[1] - max_intensity1[1];
  delete max_intensity1;
  delete max_intensity2;
  this->translation(diff_x,diff_y);
  this->display_Mat();
  float percentage = 0.2;
  std::vector<int> list_px, list_py;
  std::vector<float> list_l;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = -(int)(percentage*m_width) + 1; k < (int)(percentage*m_width); k++) {
    list_px.push_back(k);
  }
  for (int k = -(int)(percentage*m_height) + 1; k < (int)(percentage*m_height); k++) {
    list_py.push_back(k);
  }
  for (unsigned int j = 0; j < list_px.size(); j++) {
    for (unsigned int k = 0; k < list_py.size(); k++) {
      float l = this->compute_l_xy(modele, list_px[j], list_py[k], squared, copy_intensity_array);
      list_l.push_back(l);
      if (plot == true) {
        fichier << list_px[j] << " " << list_py[k] << " " << l << std::endl;
      }
    }
  }
  if (plot == true) {
    fichier.close();
  }
  int index = optimize(list_l,squared);
  p[0] = list_px[index/list_py.size()] + diff_x;
  p[1] = list_py[index%list_py.size()] + diff_y;
}


void Image::opti_rough(float p[3], Image &modele, bool squared){
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  std::vector<int> list_px;
  std::vector<int> list_py;
  std::vector<float> list_angles;
  std::vector<float> list_l;
  for (int k = (int)((int)(-m_width)/2); k < (int)(m_width/2); k+=10) {
    list_px.push_back(k);
  }
  for (int k = (int)((int)(-m_height)/2); k < (int)(m_height/2); k+=10) {
    list_py.push_back(k);
  }
  for (float k = -M_PI/2; k < M_PI/2; k+=0.3) {
    list_angles.push_back(k);
  }
  for (unsigned int i = 0; i < list_angles.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      for (unsigned int k = 0; k < list_px.size(); k++) {
        float l = this->compute_l_rxy(modele, list_px[k], list_py[j], list_angles[i], squared, copy_intensity_array);
        list_l.push_back(l);
      }
    }
  }
  int index = optimize(list_l,squared);
  p[0] = list_px[((index)%(list_px.size()*list_py.size()))%list_px.size()];
  p[1] = list_py[((index)%(list_px.size()*list_py.size()))/list_px.size()];
  p[2] = list_angles[(int)((float)index)/(float)(list_px.size()*list_py.size())];
  m_intensity_array = copy_intensity_array;
}

void Image::opti_greedy_fast_rxy(float p[3], Image &modele, bool squared){
  this->opti_rough(p, modele, squared);
  std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
  std::vector<int> list_px, list_py;
  std::vector<float> list_l;
  std::vector<float> list_angles;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = p[0] -12; k < p[0] + 12; k+=2) {
    list_px.push_back(k);
  }
  for (int k = p[1] -12; k < p[1] + 12; k+=2) {
    list_py.push_back(k);
  }
  for (float k = p[2] - 0.7; k < p[2] + 0.7; k+=0.1) {
    list_angles.push_back(k);
  }
  for (unsigned int i = 0; i < list_angles.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      for (unsigned int k = 0; k < list_px.size(); k++) {
        float l = this->compute_l_rxy(modele, list_px[k], list_py[j], list_angles[i], squared, copy_intensity_array);
        list_l.push_back(l);
      }
    }
  }
  int index = optimize(list_l,squared);
  p[0] = list_px[((index)%(list_px.size()*list_py.size()))%list_px.size()];
  p[1] = list_py[((index)%(list_px.size()*list_py.size()))/list_px.size()];
  p[2] = list_angles[(int)((float)index)/(float)(list_px.size()*list_py.size())];
}

bool equal_vector(std::vector<float> &v, std::vector<float> &w){
  for (unsigned int k = 0; k < v.size(); k++){
    if (std::abs(v[k] - w[k]) > 0.001 ) {
      return false;
    }
  }
  return true;
}

void Image::coord_descent(float p_0[3], Image &modele, bool squared, bool plot){
  std::ofstream fichier;
  if (plot == true) {
    std::string nom_fichier = "../results/coord_descent_" + m_name + ".txt";
    fichier.open(nom_fichier.c_str(), std::ios::out);
    if (fichier.fail()) {
      std::cerr << " Impossible d'ouvrir le fichier ! " << std::endl;
    }
  }
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  float l;
  std::vector<float> alpha {0.1, 0.1, 0.1};
  std::vector<float> zeros {0.0, 0.0, 0.0};
  l = this->compute_l_rxy(modele, p_0[0], p_0[1], p_0[2], squared, copy_intensity_array);
  while (not equal_vector(alpha,zeros)) {
    if (plot == true) {
      fichier << l << std::endl;
    }
    this->one_step_opti(squared, modele, p_0, alpha, 0, l, copy_intensity_array);
    this->one_step_opti(squared, modele, p_0, alpha, 1, l, copy_intensity_array);
    this->one_step_opti(squared, modele, p_0, alpha, 2, l, copy_intensity_array);
  }
  if (plot == true) {
    fichier << l << std::endl;
  }
  if (plot){
    fichier.close();
  }
}

void Image::one_step_opti(bool squared, Image &modele, float p_0[3], std::vector<float> &alpha, int k, float &l, std::vector<float> &copy_intensity_array){
  float l_increased, l_decreased;
  float p_copy[3];
  copy_tab3(p_copy, p_0);
  if (squared) {
    //Try to increment of alpha
    p_0[k] *= 1+alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_increased = this->squared_error(modele);
    m_intensity_array = copy_intensity_array;
    copy_tab3(p_0, p_copy);
    //Try to decrement of alpha
    p_0[k] *= 1-alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_decreased = this->squared_error(modele);
    m_intensity_array = copy_intensity_array;
    copy_tab3(p_0, p_copy);
    //Keep the best p
    if (l_increased < l && l_decreased > l_increased) {
      l = l_increased;
      p_0[k] = p_0[k]*(1+alpha[k]);
      alpha[k] += 0.1;
    } else if (l_decreased < l && l_decreased < l_increased) {
      l = l_decreased;
      p_0[k] = p_0[k]*(1-alpha[k]);
      alpha[k] += 0.1;
    } else {
      alpha[k] *= 0.5;
    }
  //Same thing with the other loss function
  } else {
    p_0[k] *= 1+alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_increased = this->correlation(modele);
    m_intensity_array = copy_intensity_array;
    copy_tab3(p_0, p_copy);
    p_0[k] *= 1-alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_decreased = this->correlation(modele);
    m_intensity_array = copy_intensity_array;
    copy_tab3(p_0, p_copy);
    if (l_increased > l && l_decreased < l_increased) {
      l = l_increased;
      p_0[k] = p_0[k]*(1+alpha[k]);
      alpha[k] += 0.1;
    } else if (l_decreased > l && l_decreased > l_increased) {
      l = l_decreased;
      p_0[k] = p_0[k]*(1-alpha[k]);
      alpha[k] += 0.1;
    } else {
      alpha[k] *= 0.5;
    }
  }
}

void copy_tab3(float tab1[3], float tab2[3]){
  for (int k=0; k<3; k++) {
    tab1[k] = tab2[k];
  }
}


// std::vector<float> Image::opti_rot(Image &modele, bool squared){
//   std::vector<float> list_angles;
//   std::vector<float> list_l;
//   std::vector<float> copy_intensity_array(m_size);
//   copy_intensity_array = m_intensity_array;
//   Image modele_sym = modele.symetrize();
//   Image modele_dft = modele_sym.DFT();
//   for (float k = 0; k < M_PI/2.0; k+= 0.1) {
//     list_angles.push_back(k);
//   }
//   for (int k = 0; k < list_angles.size(); k++) {
//     std::cout << "k " << k << " " << list_angles[k] << std::endl;
//     this->rotate_bilinear(list_angles[k],Pixel(m_width/2,m_height/2,0));
//     this->display_Mat();
//     Image m_sym = this->symetrize();
//     m_sym.display_Mat();
//     Image m_dft = m_sym.DFT();
//     m_dft.display_Mat();
//     modele_dft.display_Mat();
//     Image error = m_dft.Absolute_error_image(modele_dft);
//     error.display_Mat();
//     if (squared){
//       std::cout << "l " << m_dft.squared_error(modele_dft) << std::endl;
//       list_l.push_back(m_dft.squared_error(modele_dft));
//     } else {
//       std::cout << "angle " << list_angles[k] << std::endl;
//       list_l.push_back(m_dft.correlation(modele_dft));
//     }
//     m_intensity_array = copy_intensity_array;
//   }
//   int index = optimize(list_l,squared);
//   std::vector<float> p(1);
//   p[0] = list_angles[index];
//   std::vector<float> new_list_l(4);
//   std::vector<float> new_list_angles(4);
//   new_list_angles[0] = p[0];
//   new_list_angles[1] = M_PI - p[0];
//   new_list_angles[2] = 2*M_PI- p[0];
//   new_list_angles[3] = M_PI + p[0];
//   for (int k = 0; k < 4; k++){
//     this->rotate_bilinear(new_list_angles[k],Pixel(m_width/2,m_height/2,0));
//     std::cout << "angle " << new_list_angles[k] << std::endl;
//     this->display_Mat();
//     if (squared){
//       std::cout << "l " << this->squared_error(modele) << std::endl;
//       new_list_l[k] = this->squared_error(modele);
//     } else {
//       new_list_l[k] = this->correlation(modele);
//     }
//     m_intensity_array = copy_intensity_array;
//   }
//   index = optimize(new_list_l,squared);
//   p[0] = new_list_angles[index];
//   std::cout << p[0] << std::endl;
//   return p;
// }


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
//       for (int k = 0; k < list_px.size(); k++){
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
//       for (int k = 0; k < list_l.size(); k++) {
//         if (list_l[k] == l_min) {
//           new_list_px.push_back(list_p[k]);
//         }
//       }
//       list_px = new_list_px;
//     }
//   }
//   return list_px[0];
// }
