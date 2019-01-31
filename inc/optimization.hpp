#ifndef DEF_OPTIMIZATION
#define DEF_OPTIMIZATION

#include "image.hpp"
#include <assert.h>
/*!
    *  \fn int optimize(std::vector<float> list_l, bool squared)
    *  \brief Find the index of the maximum or the minimum (correlation or squared error) of the values of loss function in the vector.
    *
    *  \param a vector of the loss function values for a set of images, a boolean which is true if the loss function used is the squared error, false if it's the correlation.
    *  \return the index of the optimized value in the vector
    */
int optimize(std::vector<float> list_l, bool max);

/*!
    *  \fn bool equal_vector(std::vector<float> &v, std::vector<float> &w)
    *  \brief Function which return true if the two vectors are equals down to 0.001, false otherwise.
    *
    *  \param two vectors of floats
    */
bool equal_vector(std::vector<float> &v, std::vector<float> &w);

/*!
    *  \brief Made a copy of a table of size 3 in an other.
    *
    *  \param two tables of size 3.
    */
void copy_tab3(float tab1[3], float tab2[4]);

#endif
