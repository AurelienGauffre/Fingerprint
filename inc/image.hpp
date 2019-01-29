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
    std::vector<float> m_intensity_array; /*!< 1D array of intensities scaled from 0 to 1 reprensenting our image.*/
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    cv::Mat *m_original_image; /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_intensity_array.*/
    std::string m_name;
    Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic> m_intensity_matrix;
  public:
    Image(cv::Mat& image,const std::string& name);
    ~Image();
    float get_intensity(unsigned int k)const; /*! \param k : index * \return Intensity at index k of m_intensity_array.*/
    float *get_pointer(unsigned int k); /*! \param k : index * \return Pointer towards k-th intensity in m_intensity_array .*/
    cv::Mat* get_original_image(); /*! \param k : index * \return Adress of Mat object representing the image.*/
    void display_attributes(); /*! \brief Displays all attributes of Image, including the full m_intensity_array.*/
    void back_to_Mat();  /*!< Update the Mat version of Image*/
    void display_Mat(); /*!< Display the image in a new Window.*/
    float min_intensity() const; /*! \return Minimum intensity in m_intensity_array*/
    float max_intensity() const; /*! \return Maximum intensity in m_intensity_array*/
    void save_Mat(std::string name = ""); /*! \brief Saves the image in folder "results" */
    void draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height); /*! \brief Draws rectangle * \param intensity : intensity of rectangle (0 to 1)
                                                                                                                                       * \param origine : Coordinates of top left point */
    unsigned int coord_to_index(unsigned int x, unsigned int y); /*! \return : 1D Index in m_intensity_array*/

    // Symmetries
    void symetry_x(); /*! \brief Vertical symmetry */
    void symetry_y(); /*! \brief Horizontal symmetry */
    void symetry_diag(); /*! \brief Symmetry along diagonal x=y*/
    Image symetrize(); /*! \return New image containing all symmetries vesrions */

    // Pressure //
    /*!
        *  \brief Application of a weight function (Exponential) on the pixels to keep just a circle of the fingerprint.
        *  \param Coordinates of the circle center.
        */
    void weight_coeff(unsigned int x_spot, unsigned int y_spot);
    /*!
        *  \brief Application of a weight function (Exponential) on the pixels to keep just an ellipse of the fingerprint.
        *  \param percentage of variation of the ellipse size.
        */
    void weight_coeff_ellipse(float percentage);
    /*!
        *  \brief Method to find the pixel of the image at the intersection between the row and the column with the max of intensity.
        *  \return Pointer to the coordinates of the pixel found.
        */
    unsigned int *find_max_intensity();
    /*!
        *  \brief Method to find the parameters of the ellipse that best represents the finger.
        *  \return Pointer to the coordinates of the ellipse middle, its width and its height.
        */
    unsigned int *find_ellipse();

    // Rotation //
    std::vector<Pixel> convert_to_pixels();  /*!< Convert the m_intensity values in a vector of Pixel whose position (x,y)  are now float*/
    std::vector<Pixel> rotate_pixels(std::vector<Pixel>& Pixel_array, float angle, Pixel rot_Pixel); /*!< Returns array of rotated pixels (but keep same order than convert_to_pixels)*/
    void rotate(float angle, const Pixel& rot_point);
    void rotate_bilinear(float angle, const Pixel& rot_point);
    void bilinear_interpolation(std::vector<Pixel> &former_pixels);

    // Warp //
    std::vector<Pixel> warp_pixels(std::vector<Pixel>& Pixel_array, float strength,  Pixel& location, float radius, int violence); /*!< Returns array of warpped pixels (but keep same order than convert_to_pixels)*/
    void warp(float strength,  Pixel &location, float radius, int violence); /*!< \brief Warps a part of image \param strength : "strength" of rotation \param location : pixel around which the warps occurs*/
    // Translation //
    /*!
        *  \brief Translates the image using translate_pixels and bilinear_interpolation.
        *  \param floats parameters p_x and p_y of translation.
        */
    void translation(float p_x,float p_y);
    /*!
        *  \brief Translates the pixel array of p_x along the x axis and of p_y along the y axis.
        *
        *  \param vector of the image pixels, floats parameters p_x and p_y of translation.
        */
    std::vector<Pixel> translate_pixels(std::vector<Pixel>& Pixel_array,float p_x,float p_y);

    // Optimization //
    Image Absolute_error_image(Image &modele); /*!< Computes the absolute error image between the image and the model */
    /*!
        *  \brief lost function : sum of squared errors between the pixels of two images.
        *  \param Image : the modele image
        */
    float squared_error(Image &modele);
    /*!
        *  \brief lost function : Correlation between the pixels of two images.
        *  \param Image : the modele image
        */
    float correlation(Image &modele);
    /*!
        *  \brief Mean of its pixels.
        */
    float mean();
    /*!
        *  \brief Covariance between the pixels of two images.
        *  \param Image : the modele image
        */
    float covariance(Image &other);
    /*!
        *  \brief Greedy strategy to optimize the integer parameter of translation along the x-axis of the image, in order to correspond to the modele.
        *  \param variable in which we put the best parameter, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_greedy_x(float &p,Image &modele,bool squared);
    /*!
        *  \brief Greedy strategy to optimize the couple of integer parameters of translations along the x and y axis of the image, in order to correspond to the modele.
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_greedy_xy(float p[2],Image &modele,bool squared);
    /*!
        *  \brief Faster greedy strategy to optimize the couple of integer parameters of translations along the x and y axis of the image, in order to correspond to the modele.
        *
        *  A first translation is done to match the pixel with the maximum of intensity of each image. The greedy strategy is apply on a lower number of pixels around this point.
        *
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_greedy_fast_xy(float p[2],Image &modele, bool squared, bool plot);
    /*!
        *  \brief Faster greedy strategy to optimize the couple of integer parameters of translations along the x and y axis of the image and the parameter of rotation, in order to correspond to the modele.
        *
        *  The greedy strategy is applied on a little number of pixels around the values of the parameters found by the function opti_rough, to affine them.
        *
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_greedy_fast_rxy(float p[3],Image &modele, bool squared);
    /*!
        *  \brief Optimize the couple of float parameters of translations along the x and y axis of the image, in order to correspond to the modele.
        *
        *  It uses the function opti_greedy_fast_xy to find the integer parameter and by dichotomy finds the float ones.
        *
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_subpixel(float p[2],Image &modele, bool squared);
    /*!
        *  \brief Compute the loss function between the modele and the image translated.
        *
        *  The image is translated to compute the loss function and then put back to the original image in the function.
        *
        *  \param Image : the modele image, the parameter of translation along the x-axis, the parameter of translation along the y-axis,
        *  a boolean which is true if the loss function used is the squared error, false if it's the correlation, a copy of the pixel of the image before modifications.
        *  \return the value of the loss function
        */
    float compute_l_xy(Image &modele, float px, float py, bool squared, std::vector<float> &copy_intensity_array);
    /*!
        *  \brief Compute the loss function between the modele and the image translated and rotated.
        *
        *  The image is translated and rotated to compute the loss function and then put back to the original image in the function.
        *
        *  \param Image : the modele image, the parameter of translation along the x-axis, the parameter of translation along the y-axis, the parameter of rotation,
        *  a boolean which is true if the loss function used is the squared error, false if it's the correlation, a copy of the pixel of the image before modifications.
        */
    float compute_l_rxy(Image &modele, float px, float py, float angle, bool squared, std::vector<float> &copy_intensity_array);
    // std::vector<float> opti_rot(Image &modele, bool squared); /*!< Greedy strategy to find the angle of rotation using a DFT */
    /*!
        *  \brief Rough optimization of the parameters of translations along the x and y axis and of rotation, in order to correspond to the modele.
        *
        *  Only 1/100 of the pixels are tested to give a first approximation of the parameters of optimization.
        *
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void opti_rough(float p[3], Image &modele, bool squared);
    /*!
        *  \brief Strategy of coordinates descent to affine the values of the parameters of translations and rotation, in order to correspond perfectly to the modele.
        *
        *  The algorithm of coordinates descent is applied from the reslut of a first greedy strategy solution.
        *
        *  \param table in which we put the best parameters, the modele image, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
        */
    void coord_descent(float p_0[3],Image &modele, bool squared);
    /*!
        *  \brief Compute one step on the algorithm of coordinates descent for one parameter.
        *
        *  \param  a boolean : true if the loss function used is the squared error, false if it's the correlation, the modele image,
        *  table in which we put the parameters, a vector with the percentages of increasing or decreasing of each parameter, the value of the loss function, a copy of the pixel values of the original image.
        */
    void one_step_opti(bool squared, Image &modele, float p_0[3], std::vector<float> &alpha, unsigned int k, float &l, std::vector<float> &copy_intensity_array);

    // Linear filtering //
    void convolute_classic(std::vector<float> kernel);
    void convolute_opti(std::vector<float> kernel_col, std::vector<float> kernel_line);
    void convolute_blur(float size,float r,float s);
    cv::Mat fourier_convolution(cv::Mat& kernel);

    // DFT //
    Image DFT();

    // Operation //
    Image& operator-(float value);
    Image& operator+(float value);
    Image& operator*(float value);

};



#endif
