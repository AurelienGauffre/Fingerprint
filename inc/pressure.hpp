#ifndef DEF_PRESSURE
#define DEF_PRESSURE

#include "image.hpp"

/*!
    *  \fn float weight_exp(float coeff, unsigned int power, float r)
    *  \brief Exponential attenuation function.
    *
    *  \param Image : float : coefficient of attenuation, unsigned int : power, float : parameter.
    */
float weight_exp(float coeff, unsigned int power, float r);  /*!< Approximation of the rectangular function*/

#endif
