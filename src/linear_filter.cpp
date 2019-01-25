#include "linear_filter.hpp"

using namespace cv;

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
  std::cout <<  between(-1,0,m_width)<< std::endl ;
  m_intensity_array = new_intensity ;
  *this = (*this-mini_intensity)*(1/(maxi_intensity-mini_intensity)) ;
}

<<<<<<< HEAD
cv::Mat Image::convolute_dft(std::vector<float> kernel) {

}
=======
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
>>>>>>> f2bdc2cda1305dc9bf43b886e9c9f01df1978b69

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

void updateResult(Mat complex)
{
Mat work;
idft(complex, work);
Mat planes[] = {Mat::zeros(complex.size(), CV_32F), Mat::zeros(complex.size(), CV_32F)};
split(work, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

magnitude(planes[0], planes[1], work);    // === sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
normalize(work, work, 0, 1, NORM_MINMAX);
imshow("result", work);
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

Mat updateMag(Mat complex )
{

Mat magI;
Mat planes[] = {Mat::zeros(complex.size(), CV_32F), Mat::zeros(complex.size(), CV_32F)};
split(complex, planes);                // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))

magnitude(planes[0], planes[1], magI);    // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)

// switch to logarithmic scale: log(1 + magnitude)
magI += Scalar::all(1);
log(magI, magI);

shift(magI);
normalize(magI, magI, 1, 0, NORM_INF); // Transform the matrix with float values into a
         return magI;                                 // viewable image form (float between values 0 and 1).
//imshow("spectrum", magI);
 }

 Mat createGausFilterMask(Size imsize, int radius, float sigma_clip) {

   // call openCV gaussian kernel generator
   double sigma = (radius/sigma_clip+0.5f);
   Mat kernelX = getGaussianKernel(2*radius+1, sigma, CV_32F);
   Mat kernelY = getGaussianKernel(2*radius+1, sigma, CV_32F);
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

 float search_max(const Mat& image) {
   int i = 0;
   float maxi = 0.0;
   while (i<image.rows*image.cols) {
     float cur = (float)image.at<uchar>(i%image.cols, i/image.rows);
     if (cur>maxi) {
       maxi = cur;
     }
     i++;
   }
 }

void Image::fourier_convolution(Mat& kernel)
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
   std::cout <<"Type paddded :"<< padded.type() << '\n';
   dft(padded, DFTimage, DFT_COMPLEX_OUTPUT);

   // Forming the Gaussian filter
   imshow("Kernel", kernel);
   cv::waitKey(0);
   shift(kernel);
   imshow("Kernel", kernel);
   cv::waitKey(0);
   std::cout <<"Type kernel :"<< kernel.type() << '\n';
   Mat kernel_converted;
   //std::cout << kernel << '\n';
   kernel.convertTo(kernel_converted, CV_32F);
   std::cout <<"Type kernel :"<< kernel_converted.type() << '\n';
   Mat DFTkernel;
   dft(kernel_converted, DFTkernel, DFT_COMPLEX_OUTPUT);

   // Convolution
   std::cout << DFTimage.type() << '\n';
   std::cout << DFTkernel.type() << '\n';
   mulSpectrums(DFTimage, DFTkernel, DFTimage, 0);

   // Display Fourier-domain result
   Mat magI = updateMag(DFTimage);
   imshow("spectrum magnitude", magI);
   cv::waitKey(0);
   // IDFT
   Mat work;
   idft(DFTimage, work, DFT_REAL_OUTPUT); // <- NOTE! Don't inverse transform log-transformed magnitude image!

   Mat output_image;
   //std::cout << work << '\n';
   work.convertTo(output_image, CV_8UC1, 1.0/search_max(work)*255.0);
   imshow("spectrum magnitude", output_image);
   cv::waitKey(0);
   *(this->get_original_image()) = output_image;

}
