#include "image.hpp"
#include "pixel.hpp"
#include <iostream>

/*!
     *  \brief Coordinates of pixels
     *  \return array of Pixels corresponding to pixels coordinates, in order of pixels
     */
std::vector<Pixel> Image::convert_to_pixels() {
  std::vector<Pixel> Pixel_array;
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      Pixel_array.push_back(Pixel(x,y, m_intensity_array[coord_to_index(x,y)]));
    }
  }
  return Pixel_array;
}

/*!
  *  \brief Coordinates of pixels
  *  \param listSongs : name of image
  *  \return array of Pixels
  */
std::vector<Pixel> Image::rotate_pixels(std::vector<Pixel> Pixel_array, float angle, Pixel rot_Pixel) {
  std::vector<Pixel> Pixel_array_rotated;
  for (unsigned int i = 0; i < Pixel_array.size(); i++) {
    Pixel_array_rotated.push_back(Pixel_array[i].rotation(rot_Pixel, angle));
  }
  return Pixel_array_rotated;
}

/*!
  *  \brief Rotates the Image
  */
void Image::rotate(float angle, Pixel rot_point) {
  std::vector<Pixel> pixels(this->convert_to_pixels());
  std::vector<Pixel> rotated_pixels(this->rotate_pixels(pixels,angle, rot_point));
  std::vector<float> new_pixels_array(m_size, 1);
  for (unsigned int i = 0; i < m_size; i++) {
    signed int x_coord = (signed int)rotated_pixels[i].get_x();
    signed int y_coord = (signed int)rotated_pixels[i].get_y();
    if ((x_coord < (int)m_height)&&(x_coord >= 0)&&(y_coord < (int)m_width)&&(y_coord>=0)) {
      new_pixels_array[coord_to_index(x_coord, y_coord)] = m_intensity_array[i];
    }
  }
  m_intensity_array = new_pixels_array;
}


void Image::rotate_bilinear(float angle, Pixel rot_point) {
  std::vector<Pixel> pixels(this->convert_to_pixels());
  std::vector<Pixel> former_pixels(this->rotate_pixels(pixels,-angle, rot_point));
  std::vector<float> new_pixels_array(m_size, 1);
  for (unsigned int i = 0; i < m_size; i++) {
    float x = former_pixels[i].get_x();
    float y = former_pixels[i].get_y();
    int x1 = (int)x ;
    int x2 = x1 + 1 ;
    int y1 = (int)y ;
    int y2 = y1 + 1 ;

    if ((x1 < (int)m_width)&&(x1 >= 0)&&(y1 < (int)m_height)&&(y1>=0)) {
      new_pixels_array[i] =  former_pixels[coord_to_index(x1,y1)].get_intensity()*(x2-x)*(y2-y)+former_pixels[coord_to_index(x2,y1)].get_intensity()*(x-x1)*(y2-y)+former_pixels[coord_to_index(x1,y2)].get_intensity()*(x2-x)*(y-y1)+former_pixels[coord_to_index(x2,y2)].get_intensity()*(x-x1)*(y-y1);
    }
    else{
      new_pixels_array[i] = 1; // Test with grey value
    }
  }
  m_intensity_array = new_pixels_array;
}
