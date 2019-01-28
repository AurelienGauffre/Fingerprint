/*!
 * \file elasticity.cpp
 * \brief Definition of methods concerning the elasticity phenomenon of skin
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 14/08/2019
 */

#include "image.hpp"

std::vector<Pixel> Image::warp_pixels(std::vector<Pixel> &Pixel_array, float strength, Pixel &location, float radius, int violence)
{
    float radius_threshold = 2*radius;
    int x_min = std::max(static_cast<int>(location.get_x())-static_cast<int>(radius_threshold), static_cast<int>(0));
    int x_max = std::min(static_cast<int>(location.get_x()) + static_cast<int>(radius_threshold), static_cast<int>(m_width));
    int y_min = std::max(static_cast<int>(location.get_y()) - static_cast<int>(radius_threshold), static_cast<int>(0));
    int y_max = std::min(static_cast<int>(location.get_y()) + static_cast<int>(radius_threshold), static_cast<int>(m_height));
    for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
            if (location.distance(Pixel_array[this->coord_to_index(x,y)]) <= radius_threshold) {
                Pixel_array[this->coord_to_index(x, y)].warp(location, strength, radius, violence);
            }
        }
    }
    return Pixel_array;
}

/*!
     *  Apply warp and interpolation on image. The interpolation is done on the whole image.
     */
void Image::warp(float strength, Pixel &location, float radius, int violence)
{
    std::vector<Pixel> pixels(this->convert_to_pixels());
    std::vector<Pixel> former_pixels(this->warp_pixels(pixels, -strength, location, radius, violence));
    this->bilinear_interpolation(former_pixels);
}
