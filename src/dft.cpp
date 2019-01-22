#include "image.hpp"

Image Image::DFT(){
  int height = cv::getOptimalDFTSize(m_original_image->rows);
  int width = cv::getOptimalDFTSize(m_original_image->cols);
  cv::copyMakeBorder(*m_original_image,*m_original_image,0,height - m_original_image->rows, 0, width - m_original_image->cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
  cv::Mat planes[] = {cv::Mat_<float>(*m_original_image), cv::Mat::zeros(m_original_image->size(), CV_32F)};
  cv::Mat complex;
  cv::merge(planes, 2, complex);
  cv::dft(complex,complex);
  cv::split(complex, planes);
  cv::magnitude(planes[0], planes[1], planes[0]);
  cv::Mat magnitude = planes[0];
  magnitude += cv::Scalar::all(1);
  log(magnitude, magnitude);
  magnitude = magnitude(cv::Rect(0, 0, magnitude.cols & -2, magnitude.rows & -2));
  int cx = magnitude.cols/2;
  int cy = magnitude.rows/2;
  cv::Mat q0(magnitude, cv::Rect(0, 0, cx, cy));
  cv::Mat q1(magnitude, cv::Rect(cx, 0, cx, cy));
  cv::Mat q2(magnitude, cv::Rect(0, cy, cx, cy));
  cv::Mat q3(magnitude, cv::Rect(cx, cy, cx, cy));
  cv::Mat tmp;
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
  cv::normalize(magnitude, magnitude, 0, 1, cv::NORM_MINMAX);
  magnitude.convertTo(magnitude,CV_8UC1,255.0);
  Image res(magnitude,m_name.substr(0, m_name.size()-4) + "_dft.png");
  return res;
}
