
NB : This project was imported from Gitlab once it was finished and was made with 3 other contributors : Célestine Angla, Perrine Chassat and Lucas Etourneau.

# fingerprint 👆
The aim of this project is to find mathematical filters and models which best simulate artefacts that could occur during the fingerprint acquisition.
## How to use the project
Create a folder named build in the project folder. Go into this one and build the makefile with cmake. Then you can make. Finally the executable demo files are in /build/demo/. If you don't give any argument when calling the demo files, a standard image will be used, but you can test each demo file on the image you want.

```bash
fingerprint$ mkdir build
fingerprint$ cd build
#Creatiion of the Makefile :
fingerprint/build$ cmake ..
#Make :
fingerprint/build$ make
# This is how to execute a demo file :
fingerprint/build$ ./demo/rotation_demo
#If you want to test with a particular image, you can give it as an argument :
fingerprint/build$ ./demo/rotation_demo ./../ressources/clean_finger.png
# To call one of the tests :
fingerprint/build$ ./tests/test_rotation

```
:construction: Warning :construction:
You have to execute the demo and tests files from the build directory as described above if you want the standard images to be properly called.
