#ifndef DEF_TEST_IMAGE
#define DEF_TEST_IMAGE

/*!
 * \file test_image.hpp
 * \brief Basic test of Image manipulation
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 08/01/2019
 */
#include <iostream>
#include "image.hpp"
#include "pressure.hpp"
#include "optimization.hpp"
#include "maths_tools.hpp"
#include "linear_filter.hpp"

void test_image(char const *arg[]);
void test_pressure(char const *arg[]);
void test_rotation(char const *arg[], float angle, Pixel rot_point);
void test_optimization(char const *arg[]);
void test_warp(char const *arg[], float angle, Pixel rot_point, float radius, int violence);
void test_convolute(char const *arg[],std::vector<float> kernel);

#endif
