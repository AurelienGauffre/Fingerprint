/*!
 * \file image.cpp
 * \brief Definition of image class methods
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 01/08/2019
 */

#include "image.hpp"

/*!
     *  \brief Basic Image constructor
     *
     *  Constructor of class Image
     *
     *  \param listSongs : image "Mat", name
     */
Image::Image(cv::Mat& image, const std::string& name){
  char s = '/';
  int pos = 0;
  for (int k = name.size() - 1; (name[k] != s)&&(k>-1); k--){
    pos = k;
  }
  if (pos == -1){
    m_name = name;
  } else {
    m_name = name.substr(pos,name.size()-pos);
  }
  m_height = image.rows;
  m_width = image.cols;
  m_size = m_width*m_height;
  m_original_image = new(cv::Mat);
  *m_original_image = image;
  for (unsigned int i = 0; i < m_height; i++){
    for (unsigned int j = 0; j < m_width; j++){
      m_intensity_array.push_back(((int)(image.at<uchar>(i, j)))/255.0);
    }
  }
}

Image::~Image(){
  m_original_image->cv::Mat::~Mat();
  delete m_original_image;
}

float Image::get_intensity(unsigned int k){
  return m_intensity_array[k];
}

float *Image::get_pointer(unsigned int k){
  return &m_intensity_array[k];
}

void Image::data_intensity(){
  std::string nom_fichier = "../results/intensities_" + m_name + ".txt";
  std::ofstream fichier;
  fichier.open(nom_fichier.c_str(), std::ios::out);
  if (fichier.fail()) {
    std::cerr << " Impossible d'ouvrir le fichier ! " << std::endl;
  } else {
    for (unsigned int k = 0; k < m_size; k++) {
      fichier << m_intensity_array[k] << " " << std::endl;
    }
    fichier.close();
  }
}

void Image::display_attributes(){
  for (unsigned int y = 0 ; y < m_height; y++){
    for (unsigned int x = 0 ; x < m_width; x++){
      std::cout << m_intensity_array[coord_to_index(x,y)] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << m_height << " " << m_width << " " << m_size << "" << m_name << std::endl;
}

void Image::back_to_Mat(){
  resize(*m_original_image,*m_original_image,cv::Size(m_width,m_height));
  for (unsigned int y = 0; y < m_height; y++){
    for (unsigned int x = 0; x < m_width; x++){
      m_original_image->ptr<uchar>(y)[x] = (uchar)(255*m_intensity_array[coord_to_index(x,y)]);
    }
  }
}

void Image::display_Mat(){
  this->back_to_Mat();
  cv::namedWindow("result.png", 100000);
  cv::imshow("result.png", *m_original_image);
  cv::waitKey(0);
}

/*!
     *  \brief Image save
     *  Saves Image in project folder
     *  \param listSongs : name of image
     */
void Image::save_Mat(std::string name){
  this->back_to_Mat();
  if (name == ""){
    name = m_name;
  }
  name = "../results/" + name;
  (*m_original_image).convertTo(*m_original_image, CV_8UC1, 255.0);
  cv::imwrite(name,*m_original_image);
}

float Image::min_intensity(){
  return *std::min_element(m_intensity_array.begin(),m_intensity_array.end());
}
float Image::max_intensity(){
  return *std::max_element(m_intensity_array.begin(),m_intensity_array.end());
}

unsigned int Image::coord_to_index(unsigned int x, unsigned int y){
  return y*m_width + x;
}
// unsigned int *Image::index_to_coord(unsigned int k){
//   unsigned int result[2];
//   result[0] = k%m_width;
//   result[1] = k/m_width;
//   return result;
// }

void Image::draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height){
  unsigned int x_min = origine[0]; //raise error
  unsigned int y_min = origine[1];
  unsigned int x_max = std::min(x_min + width-1,m_width-1);
  unsigned int y_max = std::min(y_min + height-1,m_height-1);
  for (unsigned int x = x_min; x <= x_max; x++) {
    for (unsigned int y = y_min; y <= y_max; y++) {
      m_intensity_array[coord_to_index(x,y)] = intensity;
    }
  }
}

void Image::symetry_y(){
  for (unsigned int y = 0; y < m_height; y++){
    for (unsigned int x= 0; x < m_width/2; x++){
      float tmp = m_intensity_array[coord_to_index(x,y)];
      m_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(m_width -1 - x,y)];
      m_intensity_array[coord_to_index(m_width -1 - x,y)] = tmp;
    }
  }
}

void Image::symetry_diag(){
  std::vector<float> m_new_pixels_array;
  for (unsigned int x = 0; x < m_width; x++){
    for (unsigned int y= 0; y < m_height; y++){
      m_new_pixels_array.push_back(m_intensity_array[coord_to_index(x,y)]);
    }
  }
  m_intensity_array = m_new_pixels_array ;
  unsigned int tmp1 = m_width;
  m_width = m_height;
  m_height = tmp1;
}
