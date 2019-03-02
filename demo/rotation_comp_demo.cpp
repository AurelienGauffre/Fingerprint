#include "image.hpp"

int main(int argc, char const *argv[]) {
  (void)argc;
  Pixel rot_pix(128,144);
  cv::Mat modele;
  std::string m_name;
  if (argc == 1){
    m_name = "../ressources/clean_finger.png" ;
  }
  else{
    m_name = (std::string)argv[1];
  }
  modele = cv::imread(m_name, cv::IMREAD_GRAYSCALE);
  Image ref(modele, "reference");
  float max_error = 0;
  for (int angle = 10; angle < 360; angle+=60) {
    Image our_rot(ref);
    float angle_rad = angle/360.0*M_PI*2.0;

    our_rot.rotate_bilinear(angle_rad, rot_pix, true);
    our_rot.back_to_Mat();
    cv::Mat mat_rotated = ref.rotate_opencv(angle, rot_pix);
    Image ocv_rot(mat_rotated, "Res");
    std::cout << "Rotation of angle " << angle << " degrees." << std::endl;
    cv::imshow("resopcv.png", *ocv_rot.get_original_image());
    cv::imshow("resrot.png", *our_rot.get_original_image());
    cv::waitKey(0);
    max_error = std::max(max_error, our_rot.error_rate(ocv_rot));
  }
  std::cout << "Erreur max : " << max_error << '\n';
}
