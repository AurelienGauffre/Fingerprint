#ifndef DEF_PIXEL
#define DEF_PIXEL

#include <iostream>
#include <cmath>

class Pixel{
private:
  float m_x ;
  float m_y ;
  float m_intensity ;
public:
  Pixel(float x, float y, float intensity = 0);
  float get_x();
  float get_y();
  float get_intensity();
  float distance(Pixel p);
<<<<<<< HEAD
  void rotation(const Pixel& origin, float angle); /*!< return the Pixel rotated around origin of angle*/
  void warp(const Pixel& location, float strength, float radius, int violence);
=======
  Pixel rotation(const Pixel& origin, float angle); /*!< return the Pixel rotated around origin of angle*/

  Pixel translation_one_pixel(float p_x,float p_y);
  Pixel warp(const Pixel& location, float strength, float radius, int violence);
>>>>>>> 14e2ce9adf978d72fec5c7a247b1ba307651e48e
};

#endif
