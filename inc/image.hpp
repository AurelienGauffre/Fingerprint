#ifndef DEF_IMAGE
#define DEF_IMAGE

/*!
 * \file image.hpp
 * \brief Definition of Image class
 * \author Perrine, Célestine, Aurélien, Lucas
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string.h>
#include "pixel.hpp"


/*! \class Image
   * \brief class of the image we'll work on
   *
   *  The class is composed of several methods
   */
class Image {
  private:
    std::vector<float> m_pixels_array; /*!< 1D array of pixels reprensenting our image.*/
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    cv::Mat *m_original_image; /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_pixels_array.*/
    std::string m_name;
  public:
    Image(cv::Mat image,std::string name);
    void display_attributes();
    void back_to_Mat(); /*!< Update the Mat version of Image*/
    void display_Mat();
    float min_intensity();
    float max_intensity();
    void save_Mat(std::string name);
    void draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height);
    unsigned int coord_to_index(unsigned int x, unsigned int y);
    unsigned int *index_to_coord(unsigned int k);
    void symetry_y();
    void symetry_diag();
    std::vector<Pixel> coord_pixels();
    std::vector<Pixel> coord_pixels_rotated(std::vector<Pixel> Pixel_array, float angle, Pixel rot_Pixel);
    void rotate(float angle, Pixel rot_point);
    void rotate_bilinear(float angle, Pixel rot_point);
};

#endif
