#include<cmath>
#include "pixel.hpp"

Pixel::Pixel(float x, float y, float intensity):m_x(x),m_y(y),m_intensity(intensity)
{


}
Pixel Pixel::rotation(Pixel origin, float angle){
  float x = (m_x-origin.m_x)*cos(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_x;
  float y = (m_x-origin.m_x)*sin(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_y;
  return Pixel(x,y,m_intensity);
}

float Pixel::get_x() {
  return m_x;
}

float Pixel::get_y()
{
  return m_y;
}
