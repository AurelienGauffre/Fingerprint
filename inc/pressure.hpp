#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <vector>
#include <string.h>
#include <cmath>

#include "image.hpp"

float weight_exp(float coeff, unsigned int power, float r);

float weight_inv(float coeff, unsigned int power, float r);
