# itoa
Universe's fastest integer to ASCII conversion.
It is written in pure c language without any reference to other header files.

    itoa.h    - programming interface
    itoa.c    - definition of digits lookup table

## Building (Test)
Out-of-source build with CMake is recommended.
```
mkdir build
cd build
cmake ..
cd ..
cmake --build ./build --config Release
./test

```
