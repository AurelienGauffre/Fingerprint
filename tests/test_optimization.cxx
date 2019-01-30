#include "image.hpp"
#include "optimization.hpp"
#include <gtest/gtest.h>

TEST(optimize, max_or_min_list) {
    std::vector<float> list_l {20.0, 39.0, 43.0, 12.2};
    ASSERT_EQ(3, optimize(list_l, true));
    ASSERT_EQ(2, optimize(list_l, false));
}


TEST(opti_greedy_x_aux, px_translation) {
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
    ASSERT_EQ(3.0 , im1.opti_greedy_x_aux(px, im2, true, false));
}


TEST(opti_greedy_fast_xy_aux, px_py_translation) {
    float p[2];
    cv::Mat modele;
    std::string name_modele = "../ressources/rot_0.png";
    modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
    Image im2(modele, name_modele);
    im2.translation(3.0, 4.0);
    cv::Mat image;
    std::string name_image = "../ressources/rot_0.png";
    image = cv::imread(name_image, cv::IMREAD_GRAYSCALE);
    Image im1(image, name_image);
    float p_att[2];
    p_att[0] = 3.0;
    p_att[1] = 4.0;
    ASSERT_EQ(p_att, im1.opti_greedy_fast_xy_aux(p, im2, true, false));
}

TEST() {
  Pixel rot_pix(128,144);
  cv::Mat modele;
  std::string name_modele = "../ressources/clean_finger.png";
  modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
  Image ref(modele, "reference");
  float max_error = 0;
  for (int angle = 0; angle <= 360; angle+=5) {
    Image our_rot(ref);
    our_rot.rotate_bilinear(angle, rot_pix);

    Image ocv_rot(ref.rotate_opencv(angle, rot_pix), "Res");
    max_error = std::max(max_error, our_rot.error_rate(ocv_rot));
  }
  std::cout << "Erreur max : " << max_error << '\n';
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
