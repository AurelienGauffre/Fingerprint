#include "image.hpp"
#include "optimization.hpp"
#include <gtest/gtest.h>

TEST(optimize, max_or_min_list) {
    std::vector<float> list_l {20.0, 39.0, 43.0, 12.2};
    ASSERT_EQ(3, optimize(list_l, true));
    ASSERT_EQ(2, optimize(list_l, false));
}


TEST(opti_greedy_x, px_translation) {
    float px;
    cv::Mat modele;
    std::string name_modele = "../ressources/clean_finger.png";
    modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
    Image im2(modele, name_modele);
    im2.translation(3.0, 0);
    cv::Mat image;
    std::string name_image = "../ressources/clean_finger.png";
    image = cv::imread(name_image, cv::IMREAD_GRAYSCALE);
    Image im1(image, name_image);
    im1.opti_greedy_x(px, im2, true, false);
    ASSERT_EQ(3.0 , px);
}


TEST(opti_greedy_fast_xy, px_py_translation) {
    float p[2];
    cv::Mat modele;
    std::string name_modele = "../ressources/rot_0.png";
    modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
    Image im2(modele, name_modele);
    im2.translation(1.0, 1.0);
    cv::Mat image;
    std::string name_image = "../ressources/rot_0.png";
    image = cv::imread(name_image, cv::IMREAD_GRAYSCALE);
    Image im1(image, name_image);
    float p_att[2];
    p_att[0] = 1.0;
    p_att[1] = 1.0;
    im1.opti_greedy_fast_xy(p, im2, true, false);
    ASSERT_EQ(p_att[0], p[0]);
    ASSERT_EQ(p_att[1], p[1]);
}

TEST(coord_descent, px_py_angle) {
    float p[3];
    cv::Mat modele;
    std::string name_modele = "../ressources/logoUFRIM2AG.png";
    modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
    Image im2(modele, name_modele);
    im2.translation(-3.51,4.51);
    im2.rotate_bilinear(1.489,Pixel(13,16,0));
    cv::Mat image;
    std::string name_image = "../ressources/logoUFRIM2AG.png";
    image = cv::imread(name_image, cv::IMREAD_GRAYSCALE);
    Image im1(image, name_image);
    float p_att[3];
    p_att[0] = -3.51;
    p_att[1] = 4.51;
    p_att[2] = 1.489;
    im1.opti_greedy_fast_rxy(p,im2,true);
    im1.coord_descent(p,im2,true,false);
    ASSERT_NEAR(p_att[0], p[0], 0.001);
    ASSERT_NEAR(p_att[1], p[1], 0.001);
    ASSERT_NEAR(p_att[2], p[2], 0.001);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
