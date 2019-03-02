#ifndef DEF_LINEAR_FILTER
#define DEF_LINEAR_FILTER

/*!
 * \file linear_filter.cpp
 * \brief Definition of methods concerning the linear filtering.
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 01/21/2019
 */

#include "image.hpp"
#include "maths_tools.hpp"
#include "pressure.hpp" // We use the same kind of monotous function as in pressure.cpp to blur our image localy

void shift(cv::Mat magI); /*!< \brief : Shift subparts of input * \param magI : Image to be shifted */
cv::Mat updateMag(cv::Mat complex ); /*!< \brief : Compute the matrix of magnitude * \param complex : Matrix under complex form * \return Matrix of magnitudes */
/*!
    *  \brief  Create a mask (or kernel) by matricial multiplication between two vectors. The sum of the two vectors should equal 1 to preserve the energy by convolution.
    *  \param imsize : Size of the output Matrix
    *  \param kernelX : Must be a column vector.
    *  \param kernelY : Must be a column vector.
    *  \return : Matrix of the kernel. The kernel is placed in the middle of the matrix. The, to complete the size, we pad the matrix with zeros around the kernel.
    */
cv::Mat createFilterMask(cv::Size imsize, const cv::Mat& kernelX, const cv::Mat& kernelY);
float search_max(const cv::Mat& image); /*!< \brief : Returns the maximum intensity present in the Matrix */
std::vector<float> Mat_to_vector(const cv::Mat& matrix); /*!< Convert a mat object in a vector type */

#endif
