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

Image Image::Absolute_error_image(Image &modele){
  Image res = Image(*m_original_image, m_name.substr(0, m_name.size()-4) + "_error.png");
  for (int x = 0; x < (int)m_width; x++) {
    for (int y = 0; y < (int)m_height; y++) {
      // std::cout << m_intensity_array[coord_to_index(x,y)] << "  " << modele.get_intensity(coord_to_index(x,y)) << "  diff abs " << std::abs(m_intensity_array[coord_to_index(x,y)] - modele.get_intensity(coord_to_index(x,y))) << std::endl;
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
      // std::cout << "m_intensity " << m_intensity_array[coord_to_index(x,y)] << " modele " << modele.get_intensity(coord_to_index(x,y)) << " diff " << diff << " power " << std::pow(diff,2) << " sum " << sum << std::endl;
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

unsigned int optimize(std::vector<float> list_l, bool squarred){
  float l_opt = list_l[0];
  unsigned int index = 0;
  while (std::isnan(std::abs(l_opt))){
    index++;
    l_opt = list_l[index];
  }
  for (unsigned int k = index+1; k < list_l.size(); k++){
    if (squarred) {
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


std::vector<float> Image::opti_greedy_x(Image &modele, bool squarred){
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
  std::vector<float> p(1);
  p[0] = list_px[index];
  std::cout << "px : " << p[0] << std::endl;
  return p;
}


std::vector<float> Image::opti_greedy_xy(Image &modele, bool squarred){
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
  p[0] = list_px[index/list_py.size()];
  p[1] = list_py[index%list_py.size()];
  std::cout << "px : " << p[0] << " py : " << p[1] << std::endl;
  return p;
}


float Image::compute_l(Image &modele, float px, float py, bool squarred, std::vector<float> &copy_intensity_array){
  float l;
  if (squarred){
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


std::vector<float> Image::opti_subpixel(Image &modele, bool squarred){
  std::vector<float> p = this->opti_greedy_fast_xy(modele,squarred, false);
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  float px = p[0];
  float py = p[1];
  float l_g, l_d, px_g, px_d, py_g, py_d;
  float distance = 0.5;
  while (distance > 0.06){
    px_g = px - distance;
    px_d = px + distance;
    l_g = compute_l(modele,px_g,py,squarred,copy_intensity_array);
    l_d = compute_l(modele,px_d,py,squarred,copy_intensity_array);
    if (l_d < l_g) {
      px = px_d;
    } else {
      px = px_g;
    }
    distance = distance/2.0;
  }
  distance = 0.5;
  while (distance > 0.06){
    py_g = py - distance;
    py_d = py + distance;
    l_g = compute_l(modele,px,py_g,squarred,copy_intensity_array);
    l_d = compute_l(modele,px,py_d,squarred,copy_intensity_array);
    if (l_d < l_g) {
      py = py_d;
    } else {
      py = py_g;
    }
    distance = distance/2.0;
  }
  std::vector<float> res(2);
  res[0] = px;
  res[1] = py;
  std::cout << "px : " << res[0] << " py : " << res[1] << std::endl;
  return res;
}


std::vector<float> Image::opti_greedy_fast_xy(Image &modele, bool squarred, bool plot){
  std::ofstream fichier;
  if (plot == true) {
    std::string nom_fichier = "../results/data_opti_greedy_fast_xy_" + m_name + ".txt";
    fichier.open(nom_fichier.c_str(), std::ios::out);
    if (fichier.fail()) {
      std::cerr << " Impossible d'ouvrir le fichier ! " << std::endl;
    }
  }
  unsigned int *max_intensity1 = this->find_max_intensity();
  unsigned int *max_intensity2 = modele.find_max_intensity();
  int diff_x = max_intensity2[0] - max_intensity1[0];
  int diff_y = max_intensity2[1] - max_intensity1[1];
  this->translation(diff_x,diff_y);
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
      this->translation(list_px[j],list_py[k]);
      if (squarred){
        if (plot == true) {
          fichier << list_px[j] << " " << list_py[k] << " " << this->squared_error(modele) << std::endl;
        }
        list_l.push_back(this->squared_error(modele));
      } else {
        if (plot == true) {
          fichier << list_px[j] << " " << list_py[k] << " " << this->correlation(modele) << std::endl;
        }
        list_l.push_back(this->correlation(modele));
      }
      m_intensity_array= copy_intensity_array;
    }
  }
  if (plot == true) {
    fichier.close();
  }
  unsigned int index = optimize(list_l,squarred);
  std::vector<float> p(2);
  p[0] = list_px[index/list_py.size()] + diff_x;
  p[1] = list_py[index%list_py.size()] + diff_y;
  std::cout << "px : " << p[0] << " py : " << p[1] << std::endl;
  return p;
}


// std::vector<float> Image::opti_rot(Image &modele, bool squarred){
//   std::vector<float> list_angles;
//   std::vector<float> list_l;
//   std::vector<float> copy_intensity_array(m_size);
//   copy_intensity_array = m_intensity_array;
//   Image modele_sym = modele.symetrize();
//   Image modele_dft = modele_sym.DFT();
//   for (float k = 0; k < M_PI/2.0; k+= 0.1) {
//     list_angles.push_back(k);
//   }
//   for (unsigned int k = 0; k < list_angles.size(); k++) {
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
//     if (squarred){
//       std::cout << "l " << m_dft.squared_error(modele_dft) << std::endl;
//       list_l.push_back(m_dft.squared_error(modele_dft));
//     } else {
//       std::cout << "angle " << list_angles[k] << std::endl;
//       list_l.push_back(m_dft.correlation(modele_dft));
//     }
//     m_intensity_array = copy_intensity_array;
//   }
//   unsigned int index = optimize(list_l,squarred);
//   std::vector<float> p(1);
//   p[0] = list_angles[index];
//   std::vector<float> new_list_l(4);
//   std::vector<float> new_list_angles(4);
//   new_list_angles[0] = p[0];
//   new_list_angles[1] = M_PI - p[0];
//   new_list_angles[2] = 2*M_PI- p[0];
//   new_list_angles[3] = M_PI + p[0];
//   for (unsigned int k = 0; k < 4; k++){
//     this->rotate_bilinear(new_list_angles[k],Pixel(m_width/2,m_height/2,0));
//     std::cout << "angle " << new_list_angles[k] << std::endl;
//     this->display_Mat();
//     if (squarred){
//       std::cout << "l " << this->squared_error(modele) << std::endl;
//       new_list_l[k] = this->squared_error(modele);
//     } else {
//       new_list_l[k] = this->correlation(modele);
//     }
//     m_intensity_array = copy_intensity_array;
//   }
//   index = optimize(new_list_l,squarred);
//   p[0] = new_list_angles[index];
//   std::cout << p[0] << std::endl;
//   return p;
// }


std::vector<float> Image::opti_pixel_approx(Image &modele, bool squarred){
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  std::vector<float> kernel(81,0.01);
  this->convolute_classic(kernel);
  this->display_Mat();
  std::vector<int> list_px;
  std::vector<int> list_py;
  std::vector<float> list_angles;
  std::vector<float> list_l;
  std::vector<float> blured_intensity_array(m_size);
  blured_intensity_array = m_intensity_array;
  for (int k = (int)((int)(-m_width)/2); k < (int)(m_width/2); k+=10) {
    list_px.push_back(k);
  }
  for (int k = (int)((int)(-m_height)/2); k < (int)(m_height/2); k+=10) {
    list_py.push_back(k);
  }
  for (float k = 0; k < 2*M_PI; k+=0.5) {
    list_angles.push_back(k);
  }
  for (unsigned int i = 0; i < list_angles.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      for (unsigned int k = 0; k < list_px.size(); k++) {
        this->translation(list_px[k],list_py[j]);
        this->rotate_bilinear(list_angles[i],Pixel(m_width/2,m_height/2,0));
        if (squarred){
          list_l.push_back(this->squared_error(modele));
        } else {
          list_l.push_back(this->correlation(modele));
        }
        m_intensity_array= blured_intensity_array;
      }
    }
  }
  unsigned int index = optimize(list_l,squarred);
  std::vector<float> p(3);
  p[0] = list_px[((index)%(list_px.size()*list_py.size()))%list_px.size()];
  p[1] = list_py[((index)%(list_px.size()*list_py.size()))/list_px.size()];
  p[2] = list_angles[(int)((float)index)/(float)(list_px.size()*list_py.size())];
  std::cout << "After approx px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  m_intensity_array = copy_intensity_array;
  return p;
}


std::vector<float> Image::opti_greedy_fast(Image &modele, bool squarred){
  std::vector<float> p_approx = opti_pixel_approx(modele,squarred);
  std::vector<int> list_px, list_py;
  std::vector<float> list_l;
  std::vector<float> list_angles;
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  for (int k = p_approx[0] -15; k < p_approx[0] + 15; k+=3) {
    list_px.push_back(k);
  }
  for (int k = p_approx[1] -15; k < p_approx[1] + 15; k+=3) {
    list_py.push_back(k);
  }
  for (float k = 0; k < 6; k+=0.2) {
    list_angles.push_back(k);
  }
  for (unsigned int i = 0; i < list_angles.size(); i++) {
    for (unsigned int j = 0; j < list_py.size(); j++) {
      for (unsigned int k = 0; k < list_px.size(); k++) {
        this->translation(list_px[k],list_py[j]);
        this->rotate_bilinear(list_angles[i], Pixel(m_width/2, m_height/2, 0));
        if (squarred){
          list_l.push_back(this->squared_error(modele));
        } else {
          list_l.push_back(this->correlation(modele));
        }
        m_intensity_array= copy_intensity_array;
      }
    }
  }
  unsigned int index = optimize(list_l,squarred);
  std::vector<float> p(3);
  p[0] = list_px[((index)%(list_px.size()*list_py.size()))%list_px.size()];
  p[1] = list_py[((index)%(list_px.size()*list_py.size()))/list_px.size()];
  p[2] = list_angles[(int)((float)index)/(float)(list_px.size()*list_py.size())];
  std::cout << "After greedy_strategy : px : " << p[0] << " py : " << p[1] << " angle : " << p[2] << std::endl;
  return p;
}


bool equal_vector(std::vector<float> &v, std::vector<float> &w){
  for (unsigned int k = 0; k < v.size(); k++){
    if (std::abs(v[k] - w[k]) > 0.001 ) {
      return false;
    }
  }
  return true;
}


std::vector<float> Image::coord_descent(std::vector<float> p_0, Image &modele, bool squarred){
  std::vector<float> copy_intensity_array(m_size);
  copy_intensity_array = m_intensity_array;
  float l;
  std::vector<float> alpha {0.1, 0.1, 0.1};
  std::vector<float> zeros {0.0, 0.0, 0.0};
  this->translation(p_0[0],p_0[1]);
  this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
  if (squarred) {
    l = this->squared_error(modele);
  } else {
    l = this->correlation(modele);
  }
  m_intensity_array = copy_intensity_array;
  while (not equal_vector(alpha,zeros)) {
    this->one_step_opti(squarred, modele, p_0, alpha, 0, l, copy_intensity_array);
    this->one_step_opti(squarred, modele, p_0, alpha, 1, l, copy_intensity_array);
    this->one_step_opti(squarred, modele, p_0, alpha, 2, l, copy_intensity_array);
  }
  std::cout << "Result : px : " << p_0[0] << " py : " << p_0[1] << " angle : " << p_0[2] << std::endl;
  return p_0;
}


void Image::one_step_opti(bool squarred, Image &modele, std::vector<float> &p_0, std::vector<float> &alpha, unsigned int k, float &l, std::vector<float> &copy_intensity_array){
  float l_increased, l_decreased;
  std::vector<float> p_copy(3);
  p_copy = p_0;
  if (squarred) {
    p_0[k] *= 1+alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_increased = this->squared_error(modele);
    m_intensity_array = copy_intensity_array;
    p_0 = p_copy;
    p_0[k] *= 1-alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_decreased = this->squared_error(modele);
    m_intensity_array = copy_intensity_array;
    p_0 = p_copy;
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
  } else {
    p_0[k] *= 1+alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_increased = this->correlation(modele);
    m_intensity_array = copy_intensity_array;
    p_0 = p_copy;
    p_0[k] *= 1-alpha[k];
    this->translation(p_0[0],p_0[1]);
    this->rotate_bilinear(p_0[2],Pixel(m_width/2,m_height/2));
    l_decreased = this->correlation(modele);
    m_intensity_array = copy_intensity_array;
    p_0 = p_copy;
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
