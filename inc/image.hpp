#ifndef DEF_IMAGE
#define DEF_IMAGE

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string.h>

class Image {
  private:
    std::vector<float> m_pixels_array;
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_size;
    cv::Mat *m_original_image;
    std::string m_name;
  public:
    Image(cv::Mat image,std::string name);
    void display_attributes();
    void back_to_Mat();
    cv::Mat *get_original();
    void display_Mat();
    void save_Mat(std::string name="");
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
