#ifndef DEF_POINT
#define DEF_POINT

class Point{
private:
  float m_x ;
  float m_y ;
  float m_intensity ;
public:
  Point(float x, float y, float intensity = 0);
  void rotation(Point origin, float angle); /*!< Rotate the point around orginin of angle*/
};

#endif
