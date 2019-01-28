#ifndef DEF_OPTIMIZATION
#define DEF_OPTIMIZATION

#include "image.hpp"

unsigned int optimize(std::vector<float> list_l, bool max);

bool equal_vector(std::vector<float> &v, std::vector<float> &w);

void copy_tab3(float tab1[3], float tab2[4]);

#endif
