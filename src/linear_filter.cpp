/*!
 * \file linear_filter.cpp
 * \brief Implementation of functions used for 2D convolution
 * \author Perrine, Célestine, Aurélien, Lucas
 * \date 19.01.2019
 */

#include "linear_filter.hpp"

using namespace cv;

/*!
     *  \brief Classic 2D Convolution on Image
     *
     *  Convolute the image with a separable kernel.
     *
     *  \param listSongs : kernel under 1D std::vector form.
     */
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

            if(x-i < 0){ // The pixel is on  left of the image // HAS BEEN MODDIFIED FROM X-J TO X-J
              intensity = m_intensity_array[coord_to_index(-x+i-1,y-j)];
            }
            else{ // The pixel is on the right of the image
              intensity = m_intensity_array[coord_to_index(2*m_width-x-i+1,y-j)];
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
  m_intensity_array = new_intensity ;
  *this = (*this-mini_intensity)*(1/(maxi_intensity-mini_intensity)) ;
}


void Image::convolute_opti(std::vector<float> kernel_col,std::vector<float> kernel_line){
  int a = (int)((kernel_col.size()-1)/2);
  int b = a ;
  float mini_intensity = 0 ;
  float maxi_intensity = 1 ;
  std::vector<float> new_intensity(m_size);
  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      for(int j = -b;j<=b;j++){
        float intensity = 0 ;
        bool in_height= between(y-j,0,m_height);
        if(in_height){ // The pixel is in the image
          intensity = m_intensity_array[coord_to_index(x,y-j)];
        }
        else{ // The pixel is either over or under the image
          if(y-j < 0){ // The pixel is above the image
            intensity = m_intensity_array[coord_to_index(x,-y+j-1)];
          }
          else{ // The pixel is under the image
            intensity = m_intensity_array[coord_to_index(x,2*m_height-y-j+1)] ;
          }
        }
        res+= intensity*kernel_col[b-j];
      }
      new_intensity[coord_to_index(x,y)] = res;
    }

  }
  m_intensity_array = new_intensity ;
  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      for(int i = -a;i<=a;i++){
        float intensity = 0 ;
        bool in_width = between(x-i,0,m_width);

        if(in_width){ // The pixel is in the image
          intensity = m_intensity_array[coord_to_index(x-i,y)];
        }
        else{ // The pixel is either on the right or on the left of the image
          if(x-i < 0){ // The pixel is on  left of the image
            intensity = m_intensity_array[coord_to_index(-x+i-1,y)];
          }
          else{ // The pixel is on the right of the image
            intensity = m_intensity_array[coord_to_index(2*m_width-x-i+1,y)];
          }
        }
        res+= intensity*kernel_line[a-i];
      }
      new_intensity[coord_to_index(x,y)] = res;
      if (res>maxi_intensity) maxi_intensity = res ;

      if (res<mini_intensity) mini_intensity = res ;
    }
  }

  m_intensity_array = new_intensity ;
  *this = (*this-mini_intensity)*(1.0/(maxi_intensity-mini_intensity)) ;

}


void Image::convolute_blur(int kernel_radius,float speed){
  std::vector<float> kernel_col(2*kernel_radius+1,1.0/(2*kernel_radius+1));
  std::vector<float> kernel_line(2*kernel_radius+1,1.0/(2*kernel_radius+1));
  std::cout <<"Kernel value : "<< kernel_line[0]<< std::endl ;
  std::vector<float> kernel_identity{0,0,1,0,0};
  float mini_intensity = 0 ;
  float maxi_intensity = 1 ;
  std::vector<float> new_intensity(m_size);
  cv::Mat blur_Mat;
  blur_Mat = cv::imread("../ressources/noise4.png", cv::IMREAD_GRAYSCALE);
  Image blur_image(blur_Mat,"blur_image");

  // Autodection of the center of the finger (already used in pressure.cpp)
  unsigned int *ellipse = this->find_ellipse();
  unsigned int x_center = ellipse[0];
  unsigned int y_center = ellipse[1];

  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      for(int j = -kernel_radius;j<=kernel_radius;j++){
        float intensity = 0 ;
        bool in_height= between(y-j,0,m_height);
        if(in_height){
          intensity = m_intensity_array[coord_to_index(x,y-j)];
        }
        else{ // The pixel is either over or under the image
          if(y-j < 0){ // The pixel is above the image
            intensity = m_intensity_array[coord_to_index(x,-y+j-1)];
          }
          else{ // The pixel is under the image
            intensity = m_intensity_array[coord_to_index(x,2*m_height-y-j+1)] ;
          }
        }
        int diff_x = x - x_center;
        int diff_y = y - y_center;
        float rad = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*0.7);
        float c_r = weight_exp(1.0/ellipse[2],speed,rad);

        res+= intensity*(kernel_col[kernel_radius-j]*(1-c_r)+c_r*kernel_identity[kernel_radius-j]);
      }
      int diff_x = x - x_center;
      int diff_y = y - y_center;
      float rad = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*0.7);
      float c_r = weight_exp(1.0/ellipse[2],speed,rad);
      float c_r_2 = weight_exp(0.65/ellipse[2],speed,rad);
    //  c_r= c_r +std::abs(cos(100*x/m_width)*cos(100*y/m_height));
      new_intensity[coord_to_index(x,y)] = std::pow(c_r*res+(1-c_r)*std::max(blur_image.m_intensity_array[coord_to_index(x,y)],res),c_r_2);
    }

  }
  m_intensity_array = new_intensity ;
  for(int y = 0;  y<m_height; y++){
    for(int x = 0;  x<m_width;x++){
      float res = 0 ;
      for(int i = -kernel_radius;i<=kernel_radius;i++){
        float intensity = 0 ;
        bool in_width = between(x-i,0,m_width);

        if(in_width){ // The pixel is in the image
          intensity = m_intensity_array[coord_to_index(x-i,y)];
        }
        else{ // The pixel is either on the right or on the left of the image
          if(x-i < 0){ // The pixel is on  left of the image
            intensity = m_intensity_array[coord_to_index(-x+i-1,y)];
          }
          else{ // The pixel is on the right of the image
            intensity = m_intensity_array[coord_to_index(2*m_width-x-i+1,y)];
          }
        }

        int diff_x = x - x_center;
        int diff_y = y - y_center;
        float rad = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*0.7);
        float c_r = weight_exp(1.0/ellipse[2],speed,rad);
        res+= intensity*(kernel_col[kernel_radius-i]*(1-c_r)+c_r*kernel_identity[kernel_radius-i]);
      }
      int diff_x = x - x_center;
      int diff_y = y - y_center;
      float rad = std::sqrt(std::pow(diff_x,2) + std::pow(diff_y,2)*0.7);
      float c_r = weight_exp(1.0/ellipse[2],speed,rad);
      float c_r_2 = weight_exp(0.65/ellipse[2],speed,rad);
    //  c_r= c_r +std::abs(cos(100*x/m_width)*cos(100*y/m_height));
    new_intensity[coord_to_index(x,y)] =std::pow(c_r*res+(1-c_r)*std::max(blur_image.m_intensity_array[coord_to_index(x,y)],res),c_r_2);

      if (res>maxi_intensity) maxi_intensity = res ;

      if (res<mini_intensity) mini_intensity = res ;
    }
  }

  m_intensity_array = new_intensity ;
  *this = (*this-mini_intensity)*(1.0/(maxi_intensity-mini_intensity)) ;

}

void shift(Mat magI) {

  // crop if it has an odd number of rows or columns
  magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

  int cx = magI.cols/2;
  int cy = magI.rows/2;

  Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
  Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
  Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
  Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

  Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
  q2.copyTo(q1);
  tmp.copyTo(q2);
}

Mat updateMag(Mat complex ) {
  Mat magI;
  Mat planes[] = {Mat::zeros(complex.size(), CV_32F), Mat::zeros(complex.size(), CV_32F)};
  split(complex, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

  magnitude(planes[0], planes[1], magI);    // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)

  // switch to logarithmic scale: log(1 + magnitude)
  magI += Scalar::all(1);
  log(magI, magI);

  shift(magI);
  normalize(magI, magI, 1, 0, NORM_INF); // Transform the matrix with float values into a
  return magI;
}

Mat createFilterMask(Size imsize, const Mat& kernelX, const Mat& kernelY) {

  // create 2d gaus
  Mat kernel = kernelX * kernelY.t();

  int w = imsize.width-kernel.cols;
  int h = imsize.height-kernel.rows;

  int r = w/2;
  int l = imsize.width-kernel.cols -r;

  int b = h/2;
  int t = imsize.height-kernel.rows -b;

  Mat ret;
  copyMakeBorder(kernel,ret,t,b,l,r,BORDER_CONSTANT,Scalar::all(0));

  return ret;
}


Mat Image::fourier_convolution(Mat& kernel)
 {

   Mat* image_8bit = m_original_image;
   Mat image;
   (*image_8bit).convertTo(image, CV_32F);

   // Expand input image to optimal size, on the border add zero values
   Mat padded;
   int m = getOptimalDFTSize(image.rows);
   int n = getOptimalDFTSize(image.cols);
   copyMakeBorder(image, padded, 0, m - image.rows, 0, n -image.cols, BORDER_CONSTANT, Scalar::all(0));

   // Computing DFT
   Mat DFTimage;
   dft(padded, DFTimage, DFT_COMPLEX_OUTPUT);

   // Forming the Gaussian filter
   shift(kernel);
   Mat kernel_converted;
   kernel.convertTo(kernel_converted, CV_32F);
   Mat DFTkernel;
   dft(kernel_converted, DFTkernel, DFT_COMPLEX_OUTPUT);

   // Convolution
   mulSpectrums(DFTimage, DFTkernel, DFTimage, 0);

   // Display Fourier-domain result
   Mat magI = updateMag(DFTimage);
   imshow("spectrum magnitude", magI);
   cv::waitKey(0);

   // IDFT
   Mat work;
   idft(DFTimage, work, DFT_REAL_OUTPUT); // <- NOTE! Don't inverse transform log-transformed magnitude image!

   Mat output_image;
   work.convertTo(output_image, CV_8UC1, 255.0/16777216); // We have to rescale by 2^24, then multiply by 255.
   return output_image;
}

std::vector<float> Mat_to_vector(const Mat& matrix) {
  std::vector<float> array;
  if (matrix.isContinuous()) {
    //std::cout << "Is Continous" << '\n';
    array.assign((float*)matrix.datastart, (float*)matrix.dataend);
  } else {
    for (int i = 0; i < matrix.rows; ++i) {
      array.insert(array.end(), matrix.ptr<float>(i), matrix.ptr<float>(i)+matrix.cols);
    }
  }
  return array;
}
