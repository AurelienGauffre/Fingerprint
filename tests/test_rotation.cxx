#include "image.hpp"
#include "optimization.hpp"
#include <gtest/gtest.h>

TEST(rotate_bilinear, erreur_rotation) {
  Pixel rot_pix(128,144);
  cv::Mat modele;
  std::string name_modele = "../ressources/clean_finger.png";
  modele = cv::imread(name_modele, cv::IMREAD_GRAYSCALE);
  Image ref(modele, "reference");
  float max_error = 0;
  for (int angle = 0; angle < 360; angle+=2) {
    Image our_rot(ref);
    float angle_rad = angle/360.0*M_PI*2.0;

    our_rot.rotate_bilinear(angle_rad, rot_pix);
    our_rot.back_to_Mat();

    cv::Mat mat_rotated = ref.rotate_opencv(angle, rot_pix);
    Image ocv_rot(mat_rotated, "Res");
    max_error = std::max(max_error, our_rot.error_rate(ocv_rot));
  }
  ASSERT_LE(max_error, 0.006);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
