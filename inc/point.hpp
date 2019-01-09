#ifndef DEF_POINT
#define DEF_POINT

#include <iostream>
#include "image.hpp"

class Point1 {
  private:
    unsigned int m_x;
    unsigned int m_y;
  public:
    Point1(unsigned int x, unsigned int y);
    Point1(unsigned int k, Image image);
    unsigned int find_pixel(Image image);
    void display_coord();
};

#endif
