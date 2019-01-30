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
cv::Mat updateMag(cv::Mat complex );
cv::Mat createFilterMask(cv::Size imsize, const cv::Mat& kernelX, const cv::Mat& kernelY);
float search_max(const cv::Mat& image);
std::vector<float> Mat_to_vector(const cv::Mat& matrix);

#endif
