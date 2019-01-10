#ifndef DEF_IMAGE
#define DEF_IMAGE

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string.h>

using namespace cv;
using namespace std;


class Image {
  private:
    vector<float> m_pixels_array; /*!< 1D array of pixels reprensenting our image.*/
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    Mat *m_original_image;  /*!< We keep the Opencv image format in memory in our class to save it at the end. All the mathematical operation will be performed on the attribute m_pixels_array.*/
    string m_name;

  public:
    Image(Mat image,string name);
    void display_attributes();
    void back_to_Mat();
    Mat *get_original();
    void display_Mat();
    void save_Mat(string name="");
    float min_intensity();
    float max_intensity();
    unsigned int get_width();
    void draw_rectangle(float intensity, unsigned int origine[2], unsigned int width, unsigned int height);
    unsigned int coord_to_index(unsigned int x, unsigned int y);
    unsigned int *index_to_coord(unsigned int k);
    void symetry_y();
    void symetry_diag();
};

#endif
