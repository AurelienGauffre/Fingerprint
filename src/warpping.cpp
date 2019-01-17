/*!
 * \file elasticity.cpp
 * \brief Definition of methods concerning the elasticity phenomenon of skin
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 14/08/2019
 */

#include "image.hpp"

std::vector<Pixel> Image::warp_pixels(std::vector<Pixel>& Pixel_array, float strength,  Pixel& location) {
    float radius_threshold = 130;
    int x_min = std::max(static_cast<int>(location.get_x())-static_cast<int>(radius_threshold), static_cast<int>(0));
    int x_max = std::min(static_cast<int>(location.get_x()) + static_cast<int>(radius_threshold), static_cast<int>(m_width));
    int y_min = std::max(static_cast<int>(location.get_y()) - static_cast<int>(radius_threshold), static_cast<int>(0));
    int y_max = std::min(static_cast<int>(location.get_y()) + static_cast<int>(radius_threshold), static_cast<int>(m_height));
    for (int x = x_min; x <= x_max; x++) {
        for (int y = y_min; y <= y_max; y++) {
            if (location.distance(Pixel_array[this->coord_to_index(x,y)]) <= radius_threshold) {
                Pixel_array[this->coord_to_index(x, y)] = Pixel_array[this->coord_to_index(x, y)].warp(location, strength);
            }
        }
    }
    return Pixel_array;
}

void Image::warp(float strength,  Pixel& location)
{
    std::vector<Pixel> pixels(this->convert_to_pixels());
    std::vector<Pixel> former_pixels(this->warp_pixels(pixels, -strength, location));
    std::vector<float> new_pixels_array(m_size, 1);
    for (unsigned int i = 0; i < m_size; i++)
    {
        float x = former_pixels[i].get_x();
        float y = former_pixels[i].get_y();
        int x1 = (int)x;
        int x2 = x1 + 1;
        int y1 = (int)y;
        int y2 = y1 + 1;

        if ((x1 < (int)m_width) && (x1 >= 0) && (y1 < (int)m_height) && (y1 >= 0))
        {
            new_pixels_array[i] = former_pixels[coord_to_index(x1, y1)].get_intensity() * (x2 - x) * (y2 - y) + former_pixels[coord_to_index(x2, y1)].get_intensity() * (x - x1) * (y2 - y) + former_pixels[coord_to_index(x1, y2)].get_intensity() * (x2 - x) * (y - y1) + former_pixels[coord_to_index(x2, y2)].get_intensity() * (x - x1) * (y - y1);
        }
        else
        {
            new_pixels_array[i] = 1; // Test with grey value
        }
    }
    m_intensity_array = new_pixels_array;
}
