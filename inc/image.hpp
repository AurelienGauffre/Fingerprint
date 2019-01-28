#ifndef DEF_IMAGE
#define DEF_IMAGE
/*!
 * \file image.hpp
 * \brief Definition of Image class
 * \author Perrine, Célestine, Aurélien, Lucas
 */
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <math.h>
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
    float get_intensity(unsigned int k)const;
    float *get_pointer(unsigned int k);
    cv::Mat* get_original_image();
    void display_attributes();
    void back_to_Mat();  /*!< Update the Mat version of Image*/
    void display_Mat();
    float min_intensity() const;
    float max_intensity() const;
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
    // Translation //
    void translation(float p_x,float p_y); /*!< Translates the image using translate_pixels and bilinear_interpolation*/
    std::vector<Pixel> translate_pixels(std::vector<Pixel>& Pixel_array,float p_x,float p_y); /*!< Translates the pixel array of p_x along the x axis and of p_y along the y axis*/
    // Optimization //
    Image Absolute_error_image(Image &modele); /*!< Computes the absolute error image between the image and the model */
    float squared_error(Image &modele); /*!< Loss function squared_error */
    float correlation(Image &modele); /*!< Loss function correlation */
    float covariance(Image &other);
    float mean();
    void opti_greedy_x(float &p,Image &modele,bool squared); /*!< Greedy strategy to find the best integer parameter of translation of the image, along the x-axis, to correspond to the modele */
    void opti_greedy_xy(float p[2],Image &modele,bool squared); /*!< Greedy strategy to find the best couple of integers parameters of translation of the image, along the x and y axis, to correspond to the modele image */
    void opti_greedy_fast_xy(float p[2],Image &modele, bool squared, bool plot); /*!< Better strategy to find the best couple of integers parameter of translation, along the x-axis, of the image, to correspond to the modele image */
    void opti_greedy_fast_rxy(float p[3],Image &modele, bool squared); /*!< Better greedy strategy to find the best px, py and angle */
    void opti_subpixel(float p[2],Image &modele, bool squared); /*!< Dichomomy strategy to find subpixel translation parameters */
    float compute_l_xy(Image &modele, float px, float py, bool squared, std::vector<float> &copy_intensity_array);
    float compute_l_rxy(Image &modele, float px, float py, float angle, bool squared, std::vector<float> &copy_intensity_array);
    // std::vector<float> opti_rot(Image &modele, bool squared); /*!< Greedy strategy to find the angle of rotation using a DFT */
    void opti_rough(float p[3], Image &modele, bool squared);
    void coord_descent(float p_0[3],Image &modele, bool squared); /*!< Coordinate descent/ascent strategy to find the best p_x, p_y and angle */
    void one_step_opti(bool squared, Image &modele, float p_0[3], std::vector<float> &alpha, unsigned int k, float &l, std::vector<float> &copy_intensity_array);
    // Linear filtering //
    void convolute_classic(std::vector<float> kernel);
    cv::Mat convolute_dft(std::vector<float> kernel);
    void fourier_convolution(cv::Mat& kernel);
    // DFT //
    Image DFT();

    // operation //
    Image& operator-(float value);
    Image& operator+(float value);
    Image& operator*(float value);

};



#endif
