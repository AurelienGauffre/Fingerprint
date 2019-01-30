#include "image.hpp"
#include "optimization.hpp"
#include <gtest/gtest.h>

TEST(optimize, max_or_min_list) {
    std::vector<float> list_l {20.0, 39.0, 43.0, 12.2};
    ASSERT_EQ(3, optimize(list_l, true));
    ASSERT_EQ(2, optimize(list_l, false));
}



// TEST(opti_greedy_x_aux, px_translation) {
//     float px;
//     cv::Mat modele;
//     std::string name_modele = "../ressources/clean_finger.png";
//     modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
//     Image im2(modele, name_modele);
//     im2.translation(3.0, 0);
//     cv::Mat image;
//     std::string name_image = "../ressources/clean_finger.png";
//     image = cv::imread(name_image, cv::IMREAD_GRAYSCALE);
//     Image im1(image, name_image);
//     ASSERT_EQ(3.0 ,opti_greedy_x_aux(px, im2, squared));
//
// }

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
