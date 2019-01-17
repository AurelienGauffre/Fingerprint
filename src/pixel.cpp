#include "pixel.hpp"


Pixel::Pixel(float x, float y, float intensity):m_x(x),m_y(y),m_intensity(intensity)
{
}


float Pixel::get_x() {
  return m_x;
}

float Pixel::get_y() {
  return m_y;
}

float Pixel::get_intensity() {
  return m_intensity ;
}

float Pixel::distance(Pixel p) {
    return std::pow(std::pow(m_x - p.get_x(),2) + std::pow(m_y - p.get_y(),2),0.5);
}

void Pixel::rotation(const Pixel& origin, float angle){ // FIX To move in rotation.cpp
  float x = (m_x-origin.m_x)*cos(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_x;
  m_y = (m_x - origin.m_x) * sin(angle) + (m_y - origin.m_y) * cos(angle) + origin.m_y;
  m_x = x;
}

Pixel Pixel::translation_one_pixel(float p_x, float p_y){
  float x = m_x + p_x;
  float y = m_y + p_y;
  return Pixel(x,y,m_intensity);
}

Pixel Pixel::warp(const Pixel& location, float strength, float radius, int violence) { // FIX to move in warpping.cpp
  float d = this->distance(location);
  float theta = exp(-std::pow(d/radius, violence))*strength;
  float x = (m_x - location.m_x) * cos(theta) - (m_y - location.m_y) * sin(theta) + location.m_x;
  float y = (m_x - location.m_x) * sin(theta) + (m_y - location.m_y) * cos(theta) + location.m_y;
  return Pixel(x,y, std::pow(m_intensity, 1+exp(-d/radius)));
}
