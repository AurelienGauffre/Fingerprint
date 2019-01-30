:construction: work in progress... :construction:

# fingerprint 👆
The aim of this project is to find mathematical filters and models which best simulate artefacts that could occur during the fingerprint acquisition.
## How to use the project
Create a folder named build in the project folder. Go into this one and build the makefile with cmake. Then you can make. Finally the executable demo files are in /build/demo/. If you don't give any argument when calling the demo, a standard image will be used, but you can test each demo file on the image you want.

```bash
# create the conda environment
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./demo/rotation_demo
$ ./demo/rotation_demo ./../ressources/clean_finger.png #if you want to test with a particular image you can give it as an argument
```
