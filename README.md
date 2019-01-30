:construction: work in progress... :construction:

# fingerprint 👆
The aim of this project is to find mathematical filters and models which best simulate artefacts that could occur during the fingerprint acquisition.
## How to use the project
Create a folder named build in the project folder. Go into this one and build the makefile with cmake. Then you can make. Finally the executable demo files are in /build/demo/. If you don't give any argument when calling the demo, a standard image will be used, but you can test each demo file on the image you want.

```bash
fingerprint$ mkdir build
fingerprint$ cd build
#Creatiion of the Makefile :
fingerprint/build$ cmake ..
#Make :
fingerprint/build$ make
fingerprint/build$ ./demo/rotation_demo
#If you want to test with a particular image, you can give it as an argument :
fingerprint/build$ ./demo/rotation_demo ./../ressources/clean_finger.png
```
