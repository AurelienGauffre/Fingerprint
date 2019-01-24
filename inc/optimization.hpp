#ifndef DEF_OPTIMIZATION
#define DEF_OPTIMIZATION

#include <iostream>
#include <fstream>

#include "image.hpp"

unsigned int optimize(std::vector<float> list_l, bool max);

bool equal_vector(std::vector<float> &v, std::vector<float> &w);

#endif
