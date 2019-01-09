#include <iostream>
#include "point.hpp"

Point1::Point1(unsigned int x, unsigned int y):m_x(x),m_y(y){
}

Point1::Point1(unsigned int k, Image image){
  m_x = k%(image.get_width());
  m_y = k/(image.get_width());
}

unsigned int Point1::find_pixel(Image image){
  return m_y*image.get_width() + m_x;
}

void Point1::display_coord(){
  cout << "x : " << m_x << "y : " << m_y << endl;
}
