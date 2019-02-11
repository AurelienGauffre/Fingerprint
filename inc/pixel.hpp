#ifndef DEF_PIXEL
#define DEF_PIXEL

#include <iostream>
#include <cmath>
/*! \class Image
   * \brief A Pixel represent a 2D Points which float coordinates which has an intenisty.
   * Array of Pixels are used the class Image when when dealing with non integer coordinates, mostly during  interpolations.
   *  The basic geometrical transformation are implemented for Pixel such as translation, rotation and warping.
   */
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

  void rotation(const Pixel& origin, float angle); /*!< return the Pixel rotated around origin of angle*/

  /*!
      *  \brief return the Pixel rotated around location of angle calculated according to parameters strength,radius,violence
      *
      *  \param location : coordinates of center of rotation
      *  \param strength : rotation at the origin
      *  \param radius : radius on which the rotation remains almost constant
      *  \param violence : speed of deacreasing of the rotation at distance "radius"

           */
  void warp(const Pixel& location, float strength, float radius, int violence);
  Pixel translation_one_pixel(float p_x,float p_y);
};

#endif
