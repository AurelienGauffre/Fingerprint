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
    vector<float> m_pixels_array;
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    Mat *m_original_image;
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
    unsigned int coord_to_index(unsigned int i, unsigned int j);
    unsigned int *index_to_coord(unsigned int k);

};

#endif
