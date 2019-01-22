#include "linear_filter.hpp"


void Image::convolute_classic(std::vector<float> kernel){
  int a = ((int)(std::pow(kernel.size(),0.5))-1)/2;
  int b = a ;
  std::vector<float> new_intensity(m_size);
  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      float norm = 0 ;
      for(int i = -a;i<=a;i++){
        for(int j = -b;j<=b;j++){
          if(((between(x-i,0,m_width))&&(between(y-j,0,m_height)))){
            float kernel_value = kernel[(2*a+1)*(a-i)+(b-j)] ;
            res+=m_intensity_array[coord_to_index(x-i,y-j)]*kernel_value;
            norm += kernel_value ;
          }
        }
      }
      new_intensity[coord_to_index(x,y)] = res/norm;
    }
  }
  m_intensity_array = new_intensity ;
}

void Image::convolute_dft(std::vector<float> kernel) {
  Image image_ft = this->DFT();
  Image kernel_ft = kernel_expansion(kernel, m_width, m_height);
  kernel_ft.display_Mat();
}

Image kernel_expansion(std::vector<float> kernel, int width, int height) {
  cv::Mat extended_kernel = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
  Image im(extended_kernel, "kernel_extended");
  int a = ((int)(std::pow(kernel.size(),0.5))-1)/2;
  int x_middle = width/2-1;
  int y_middle = height/2-1;
  int x_top_left = x_middle-a;
  int y_top_left = y_middle-a;
  int kernel_index = 0;
  for (int j = y_top_left; j < y_top_left+2*a+1; j++) {
    for (int i = x_top_left; i< x_top_left+2*a+1; i++) {
      *im.get_pointer(im.coord_to_index(i,j)) = kernel[kernel_index]/255;
      kernel_index++;
    }
  }
  im.display_Mat();
  return im;
}
