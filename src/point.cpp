#include<cmath>
#include "point.hpp"

Point::Point(float x, float y, float intensity):m_x(x),m_y(y),m_intensity(intensity)
{

}
void Point::rotation(Point origin, float angle){
  m_x = (m_x-origin.m_x)*cos(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_x;
  m_y = (m_x-origin.m_x)*sin(angle)-(m_y-origin.m_y)*sin(angle)+ origin.m_y;
}
