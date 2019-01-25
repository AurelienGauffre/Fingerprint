#include "linear_filter.hpp"


void Image::convolute_classic(std::vector<float> kernel){
  int a = ((int)(std::pow(kernel.size(),0.5))-1)/2;
  int b = a ;
  float mini_intensity = 0 ;
  float maxi_intensity = 1 ;
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
            intensity = m_intensity_array[coord_to_index((m_width-1)*(1-(x-i)<0),(m_height-1)*(1-(y-j)<0))] ;
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
      if (res>maxi_intensity) maxi_intensity = res ;
      if (res<mini_intensity) mini_intensity = res ;
    }
  }
  std::cout <<  between(-1,0,m_width)<< std::endl ;
  m_intensity_array = new_intensity ;
  *this = (*this-mini_intensity)*(1/(maxi_intensity-mini_intensity)) ;
}

// void Image::convolute_dft(std::vector<float> kernel) {
//   Image kernel_image = centered_kernel_expansion(kernel, m_width, m_height);
//   cv::Mat kernel_mat = kernel_image.get_original_image();
//   int dft_M = cv::getOptimalDFTSize( m_original_image->rows+kernel_mat.rows-1 );
//   int dft_N = cv::getOptimalDFTSize( m_original_image->cols+kernel_mat.cols-1 );
//
//   cv::Mat* dft_A = cv::CreateMat( dft_M, dft_N, m_original_image->type() );
//   cv::Mat* dft_B = cv::CreateMat( dft_M, dft_N, kernel_mat.type() );
//   cv::Mat tmp;
//
//   cvGetSubRect( dft_A, &tmp, cv::Rect(0,0,m_original_image->cols,m_original_image->rows));
//   cv::Copy( &m_original_image, &tmp );
//   cvGetSubRect(
//     dft_A,
//     &tmp,
//     cv::Rect( m_original_image->cols, 0, m_original_image->cols-m_original_image->cols, m_original_image->rows )
//   );
//   cv::Zero( &tmp );
//
//   DFT( dft_A, dft_A, CV_DXT_FORWARD, m_original_image->rows );
//
//   cvGetSubRect( dft_A, &tmp, cv::Rect(0,0,kernel_mat.cols,kernel_mat.rows));
//   cv::Copy( &kernel_mat, &tmp );
//   cvGetSubRect(
//     dft_A,
//     &tmp,
//     cv::Rect( kernel_mat.cols, 0, kernel_mat.cols, kernel_mat.cols, kernel_mat.rows )
//   );
//
//   DFT( dft_B, dft_B, CV_DXT_FORWARD, kernel_image.rows );
//
//   mulSpectrums( dft_A, dft_B, dft_A, 0 );
//
//   cv::DFT( dft_A, dft_A, CV_DXT_INV_SCALE, C->rows );
//   cvGetSubRect( dft_A, &tmp, cv::Rect(0,0,conv->cols,C->rows) );
// }

Image centered_kernel_expansion(std::vector<float> kernel, int width, int height) {
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
      *im.get_pointer(im.coord_to_index(i,j)) = kernel[kernel_index];
      kernel_index++;
    }
  }
  im.display_Mat();
  return im;
}

Image zeropad_kernel_expansion(std::vector<float> kernel,int width, int height){

}
