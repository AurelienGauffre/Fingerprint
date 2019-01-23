#ifndef DEF_IMAGE
#define DEF_IMAGE
/*!
 * \file image.hpp
 * \brief Definition of Image class
 * \author Perrine, Célestine, Aurélien, Lucas
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <opencv2/core/eigen.hpp>
#include "pixel.hpp"
/*! \class Image
   * \brief class of the image we'll work on
   *
   *  The class is composed of several methods
   */
class Image {
  private:
    std::vector<float> m_intensity_array; /*!< 1D array of pixels reprensenting our image.*/
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    cv::Mat *m_original_image; /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_intensity_array.*/
    std::string m_name;
    Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> m_intensity_matrix;
  public:
    Image(cv::Mat& image,const std::string& name);
    ~Image();
    float get_intensity(unsigned int k);
    float *get_pointer(unsigned int k);
    void display_attributes();
    void data_intensity();
    void back_to_Mat(); /*!< Update the Mat version of Image*/
    void display_Mat();
    float min_intensity();
    float max_intensity();
    void save_Mat(std::string name = "");
    void draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height);
    unsigned int coord_to_index(unsigned int x, unsigned int y);
    // unsigned int *index_to_coord(unsigned int k);
    void symetry_x();
    void symetry_y();
    void symetry_diag();
    Image symetrize();
    // Pressure //
    void weight_coeff(unsigned int x_spot, unsigned int y_spot); /*!< Simulates the fingerprint with a weak pressure given the center of pressure (circle approximation)*/
    void weight_coeff_ellipse(float percentage);  /*!< Simulates the fingerprint with a weak pressure given a "percentage" of pressure (ellipse approximation) */
    unsigned int *find_max_intensity();
    unsigned int *find_ellipse(); /*!< Finds the ellipse that best represents the finger*/
    // Rotation //
    std::vector<Pixel> convert_to_pixels();  /*!< Convert the m_intensity values in a vector of Pixel whose position (x,y)  are now float*/
    std::vector<Pixel> rotate_pixels(std::vector<Pixel>& Pixel_array, float angle, Pixel rot_Pixel); /*!< Returns array of rotated pixels (but keep same order than convert_to_pixels)*/
    void rotate(float angle, const Pixel& rot_point);
    void rotate_bilinear(float angle, const Pixel& rot_point);
    void bilinear_interpolation(std::vector<Pixel> &former_pixels);
    // Warp //
    std::vector<Pixel> warp_pixels(std::vector<Pixel>& Pixel_array, float strength,  Pixel& location, float radius, int violence); /*!< Returns array of warpped pixels (but keep same order than convert_to_pixels)*/
    void warp(float strength,  Pixel &location, float radius, int violence); /*!< Warp a part of picture*/
    // Optimization //
    //int optimization(Image &modele);
    void translation(float p_x,float p_y);
    std::vector<Pixel> translate_pixels(std::vector<Pixel>& Pixel_array,float p_x,float p_y);
    std::vector<float> opti_complex(Image &modele,bool squarred);
    std::vector<float> opti_complex_xy(Image &modele,bool squarred);
    float squared_error(Image &modele);
    float correlation(Image &modele);
    float covariance(Image &other);
    float mean();
    Image Absolute_error_image(Image &modele);
    std::vector<float> opti_subpixel(Image &modele, bool squarred);
    std::vector<float> opti_rot(Image &modele, bool squarred);
    std::vector<float> opti_better(Image &modele, bool squarred, bool plot);
    float compute_l(Image &modele, float px, float py, bool squarred, std::vector<float> &copy_intensity_array);
    Image DFT();

    //Linear filtering
    void convolute_classic(std::vector<float> kernel);
    void convolute_dft(std::vector<float> kernel);

};



#endif
