/*!
 * \file linear_filter.cpp
 * \brief Definition of methods concerning the linear filtering.
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 01/21/2019
 */

#include "image.hpp"
#include "pixel.hpp"
#include "maths_tools.hpp"

Image kernel_expansion(std::vector<float> kernel,int width, int height);
