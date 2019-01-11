#ifndef DEF_PIXEL
#define DEF_PIXEL

class Pixel{
private:
  float m_x ;
  float m_y ;
  float m_intensity ;
public:
  Pixel(float x, float y, float intensity = 0);
  float x_getter();
  float y_getter();
  Pixel rotation(Pixel origin, float angle); /*!< return the Pixel rotated around orginin of angle*/
};

#endif
