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
          if(((between(x-i,0,m_width))&&(between(y-j,0,m_height)))){
            res+=m_intensity_array[coord_to_index(x-i,y-j)]*kernel[(2*a+1)*(a-i)+(b-j)];          
          }
        }
      }
      new_intensity[coord_to_index(x,y)] = res;
    }
  }
  m_intensity_array = new_intensity ;
}
