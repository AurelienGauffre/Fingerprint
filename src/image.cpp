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
  for ( int k = name.size() - 1; (k>=0)&&(name[k] != s); k--){
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
  *m_original_image = image.clone();
  m_intensity_array.resize(m_size, 0.);
  for (int i = 0; i < m_height; i++){
    for (int j = 0; j < m_width; j++){
      //Convertes intensities to float between 0 and 1
      m_intensity_array[coord_to_index(j,i)] = static_cast<float>((static_cast<int>(image.at<uchar>(i, j)))/255.0);
    }
  }
}

Image::Image(const Image& other){
  m_name = other.m_name;
  m_size = other.m_size;
  m_width = other.m_width;
  m_height= other.m_height;
  m_original_image = new(cv::Mat);
  *m_original_image = (*other.m_original_image).clone();
  m_intensity_array = other.m_intensity_array;
}

Image::~Image(){
  m_original_image->cv::Mat::~Mat();
  delete m_original_image;
}

float Image::get_intensity(int k)const{
  return m_intensity_array[k];
}

float *Image::get_pointer(int k){
  return &m_intensity_array[k];
}

cv::Mat* Image::get_original_image() {
  return m_original_image;
}


void Image::display_attributes(){
  for (int y = 0 ; y < m_height; y++){
    for (int x = 0 ; x < m_width; x++){
      std::cout << m_intensity_array[coord_to_index(x,y)] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << m_height << " " << m_width << " " << m_size << "" << m_name << std::endl;
}

void Image::back_to_Mat() {
  resize(*m_original_image,*m_original_image,cv::Size(m_width,m_height));
  for (int y = 0; y < m_height; y++){
    for (int x = 0; x < m_width; x++){
      //Converts back to integers beween 0 and 255
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
  // (*m_original_image).convertTo(*m_original_image, CV_8UC1, 255.0);
  cv::imwrite(name,*m_original_image);
}

float Image::min_intensity()const{
  return *std::min_element(m_intensity_array.begin(),m_intensity_array.end());
}
float Image::max_intensity()const{
  return *std::max_element(m_intensity_array.begin(),m_intensity_array.end());
}

int Image::coord_to_index(int x, int y){
  return y*m_width + x;
}

void Image::draw_rectangle(float intensity, int origine[2], int width, int height){
  int x_min = origine[0]; //raise error
  int y_min = origine[1];
  int x_max = std::min(x_min + width-1,m_width-1);
  int y_max = std::min(y_min + height-1,m_height-1);
  for (int x = x_min; x <= x_max; x++) {
    for (int y = y_min; y <= y_max; y++) {
      m_intensity_array[coord_to_index(x,y)] = intensity;
    }
  }
}

void Image::symetry_y(){
  for (int y = 0; y < m_height; y++){
    for (int x= 0; x < m_width/2; x++){
      float tmp = m_intensity_array[coord_to_index(x,y)];
      m_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(m_width -1 - x,y)];
      m_intensity_array[coord_to_index(m_width -1 - x,y)] = tmp;
    }
  }
}

void Image::symetry_x(){
  for (int y = 0; y < m_height/2; y++){
    for (int x= 0; x < m_width; x++){
      float tmp = m_intensity_array[coord_to_index(x,y)];
      m_intensity_array[coord_to_index(x,y)] = m_intensity_array[coord_to_index(x,m_height - 1 - y)];
      m_intensity_array[coord_to_index(x,m_height - 1 - y)] = tmp;
    }
  }
}

void Image::symetry_diag(){
  std::vector<float> m_new_pixels_array;
  for (int x = 0; x < m_width; x++){
    for (int y= 0; y < m_height; y++){
      m_new_pixels_array.push_back(m_intensity_array[coord_to_index(x,y)]);
    }
  }
  m_intensity_array = m_new_pixels_array ;
  int tmp1 = m_width;
  m_width = m_height;
  m_height = tmp1;
}

/*! Creates an image 4 times bigger, containing all 3 symmetries possibilies : Horizontal symmetry on top left,
    Diagonnal symmetry on bottom left, Vertical symmetry on bottom right,
    and Orginal image on top right.  */
Image Image::symetrize() {
  std::vector<float> m_new_intensity_array(m_size*4);
  for (int x = 0; x < m_width; x++){
    for (int y = 0; y < m_height; y++){
      m_new_intensity_array[y*2*m_width + x] = m_intensity_array[coord_to_index(x,y)];
    }
  }
  this->symetry_y();
  for (int x = 0; x < m_width; x++){
    for (int y = 0; y < m_height; y++){
      m_new_intensity_array[y*2*m_width + x + m_width] = m_intensity_array[coord_to_index(x,y)];
    }
  }
  this->symetry_x();
  for (int x = 0; x < m_width; x++){
    for (int y = 0; y < m_height; y++){
      m_new_intensity_array[(y + m_height)*2*m_width + x + m_width] = m_intensity_array[coord_to_index(x,y)];
    }
  }
  this->symetry_y();
  for (int x = 0; x < m_width; x++){
    for (int y = 0; y < m_height; y++){
      m_new_intensity_array[(y + m_height)*2*m_width + x] = m_intensity_array[coord_to_index(x,y)];
    }
  }
  cv::Mat res_mat(m_height*2,m_width*2,CV_8UC1);
  for (int y = 0; y < 2*m_height; y++){
    for (int x = 0; x < 2*m_width; x++){
      res_mat.ptr<uchar>(y)[x] = (uchar)(255*m_new_intensity_array[y*2*m_width + x]);
    }
  }
  Image res(res_mat, m_name.substr(0, m_name.size()-4) + "_symetrized.png");
  return res;
}


Image& Image::operator-(float value){
  for(int i = 0 ; i<m_size ; i++){
    m_intensity_array[i]-=value ;
  }
  return *this ;
}


Image& Image::operator+(float value){
  for(int i = 0 ; i<m_size ; i++){
    m_intensity_array[i]+=value ;
  }
  return *this ;
}


Image& Image::operator*(float value){
  for(int i = 0 ; i<m_size ; i++){
    m_intensity_array[i]*=value ;
  }
  return *this ;
}
