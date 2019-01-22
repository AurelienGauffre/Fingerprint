#include "linear_filter.hpp"
#include "maths_tools.hpp"
void Image::convolute(std::vector<float> kernel){
  int a = ((int)(std::pow(kernel.size(),0.5))-1)/2;
  int b = a ;
  std::vector<float> new_intensity(m_size);
  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      for(int i = -a;i<=a;i++){
        for(int j = -b;j<=b;j++){
          float intensity = 0 ;
          bool in_width = between(x-i,0,m_width);
          bool in_height= between(y-j,0,m_height);
          if(in_width&&in_height){ // The pixel is in the image
            intensity = m_intensity_array[coord_to_index(x-i,y-j)];
          }
          else if(!(in_width)&&!(in_height)){ // The pixel is on the diagonal of the image
            intensity = m_intensity_array[coord_to_index(m_width*(1-(x-i)<0),m_height*(1-(y-j)<0))] ;
          }
          else if(!(in_height)){ // The pixel is either over or under the image
            if(y-j < 0){ // The pixel is above the image
              intensity = m_intensity_array[coord_to_index(x-i,-y+j-1)];
            }
            else{ // The pixel is under the image
              intensity = m_intensity_array[coord_to_index(x-i,2*m_height-y-j+1)] ;
            }

          }
          else{ // The pixel is either on the right or on the left of the image

            if(x-j < 0){ // The pixel is on  left of the image
              intensity = m_intensity_array[coord_to_index(-x+i-1,y-j)];
            }
            else{ // The pixel is on the right of the image
              intensity = m_intensity_array[coord_to_index(2*m_width-x-i+1,y-j)]; ;
            }
          }
          res+= intensity*kernel[(2*a+1)*(a-i)+(b-j)];
        }
      }
      new_intensity[coord_to_index(x,y)] = res;
    }
  }
  std::cout <<  between(-1,0,m_width)<< std::endl ;
  m_intensity_array = new_intensity ;
}
