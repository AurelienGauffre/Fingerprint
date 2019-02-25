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
    int m_height;
    int m_width;
    int m_size;
    cv::Mat *m_original_image; /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_intensity_array.*/
    std::string m_name;
  public:
    Image(cv::Mat& image,const std::string& name);
    Image(const Image& other);
    ~Image();
    float get_intensity(int k)const; /*! \param k : index * \return Intensity at index k of m_intensity_array.*/
    float *get_pointer(int k); /*! \param k : index * \return Pointer towards k-th intensity in m_intensity_array .*/
    cv::Mat* get_original_image(); /*! \param k : index * \return Adress of Mat object representing the image.*/
    void display_attributes(); /*! \brief Displays all attributes of Image, including the full m_intensity_array.*/
    void back_to_Mat();  /*!< Update the Mat version of Image*/
    void display_Mat(); /*!< Display the image in a new Window.*/
    float min_intensity() const; /*! \return Minimum intensity in m_intensity_array*/
    float max_intensity() const; /*! \return Maximum intensity in m_intensity_array*/
    void save_Mat(std::string name = ""); /*! \brief Saves the image in folder "results" */
    void draw_rectangle(float intensity, int origine[2], int width, int height); /*! \brief Draws rectangle * \param intensity : intensity of rectangle (0 to 1)
                                                                                                                                       * \param origine : Coordinates of top left point */
    int coord_to_index(int x, int y); /*! \return : 1D Index in m_intensity_array*/

    // Symmetries //
    void symetry_x(); /*! \brief Vertical symmetry */
    void symetry_y(); /*! \brief Horizontal symmetry */
    void symetry_diag(); /*! \brief Symmetry along diagonal x=y*/
    Image symetrize(); /*! \return New image containing all symmetries vesrions */

    // Pressure //
    /*!
        *  \brief Application of a weight function (Exponential) on the pixels to keep just a circle of the fingerprint.
        *  \param Coordinates of the circle center.
        */
    void weight_coeff(int x_spot, int y_spot);
    /*!
        *  \brief Application of a weight function (Exponential) on the pixels to keep just an ellipse of the fingerprint.
        *  \param percentage of variation of the ellipse size.
        */
    void weight_coeff_ellipse(float percentage);
    /*!
        *  \brief Method to find the pixel of the image at the intersection between the row and the column with the max of intensity.
        *  \return Pointer to the coordinates of the pixel found.
        */
    int *find_max_intensity();
    /*!
        *  \brief Method to find the parameters of the ellipse that best represents the finger.
        *  \return Pointer to the coordinates of the ellipse middle, its width and its height.
        */
    std::array<int, 4> find_ellipse();

    // Rotation //
    std::vector<Pixel> convert_to_pixels();  /*!< \return A 1D array of Pixels representing the image*/
    std::vector<Pixel> rotate_pixels(std::vector<Pixel>& Pixel_array, float angle, Pixel rot_Pixel); /*!< \param Pixel_array : The array of pixels to be rotated * \param angle : angle of rotation * \param rot_Pixel : rotation Pixel
                                                                                                          \return Vector of pixels rotated*/
    void rotate_bilinear(float angle, const Pixel& rot_point, bool fill_black=false); /*!< \brief Calls rotate_pixels, interpolate, and apply rotation on Image * \param angle : angle of rotation * \param rot_point : rotation Pixel*/
    void bilinear_interpolation(std::vector<Pixel> &former_pixels, bool fill_black=false); /*!< \brief Change the intensities value by interpolation \param former_pixels : Array of pixels to be interpolated according their position*/
    cv::Mat rotate_opencv(float angle, Pixel& rot_point); /*!< \brief Rotation using OpenCV Library * \param angle : angle of rotation * \param rot_point : rotation Pixel*/

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
        *  \param Image : the modele image
        *  \return Sum of differences normalised to 1, divided by size.
        */
    float error_rate(Image &modele);
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
    void opti_greedy_x(float &p,Image &modele,bool squared,bool plot);
    float opti_greedy_x_aux(float &px, Image &modele, bool squared, bool plot);
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
    void coord_descent(float p_0[3],Image &modele, bool squared, bool plot);
    /*!
        *  \brief Compute one step on the algorithm of coordinates descent for one parameter.
        *
        *  \param  a boolean : true if the loss function used is the squared error, false if it's the correlation, the modele image,
        *  table in which we put the parameters, a vector with the percentages of increasing or decreasing of each parameter, the value of the loss function, a copy of the pixel values of the original image.
        */
    void one_step_opti(bool squared, Image &modele, float p_0[3], std::vector<float> &alpha, int k, float &l, std::vector<float> &copy_intensity_array);

    // Linear filtering //
    /*!
        *  \brief Convolute the image with a kernel (2D convolution).
        *  \param kernel : The kernel must be under 1D form. No need to pad the kernel.
        */
    void convolute_classic(std::vector<float> kernel);
    /*!
        *  \brief  Classic convolution of an image and a kernel
        *
        *
        *  \param  kernel : The kernel is a 1D float array whose size is a square of an odd number.
        */
    void convolute_opti(std::vector<float> kernel_col, std::vector<float> kernel_line);
    /*!
        *  \brief  Convolution with separated kernel.
        *   This convolution works by making two 1D convolution  with the two 1D Kernel given in order to optimize the time of the convolution.
        *
        *  \param  kernel_col : This  kernel is a 1D float array whose size is a an odd number. A convolution along the y axis will be performed with this kernnel.
        *  \param  kernel_line : This kernel is a 1D float array whose size is a an odd number. A convolution along the x axis will be performed with this kernnel.
        */
    void convolute_blur(int kernel_radius,float speed);
    /*!
        *  \brief  Convolution to simulate blur artefact.
        *   This convolution try to simulate the blur artefact. Unlike the other convolution, this one  uses a kernel whose values is space dependant. The center of the fingerprint and its size are self-detected.
        *
        *  \param kernel_radius : The radius of the blur kernel used. The size of the kernel will be 2*kernel_radius + 1 .
        *  \param  speed : speed of transition between the blur and sharp region.
        */
    cv::Mat fourier_convolution(cv::Mat& kernel);
    /*!
        *  \brief  Convolution in fourrier space.
        *   Convolute in fourrier space by realising a pointwise multiplication with the kernel wich is going to be shiftrf clerverly.
        *
        *  \param kernel : The kernel has to be the same size of the image, at the center of the image, and 0 padded elsewhere. The shifting of the kernel will be done inside the method.
        *
        */



    // DFT //
    Image DFT();

    // Operation //
    Image& operator-(float value);
    Image& operator+(float value);
    Image& operator*(float value);

};



#endif
