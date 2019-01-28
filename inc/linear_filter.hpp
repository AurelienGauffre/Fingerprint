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


Image zeropad_kernel_expansion(std::vector<float> kernel,int width, int height);
void updateResult(cv::Mat complex);
void shift(cv::Mat magI);
cv::Mat updateMag(cv::Mat complex );
cv::Mat createGausFilterMask(cv::Size imsize, int radius, float sigma_clip);
float search_max(const cv::Mat& image);
void Image::convolute_blur(float size,float r,float s);
#endif
