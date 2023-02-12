# itoa
Universe's fastest integer to ASCII conversion. C++11 is supported.
It is written in pure c language without any reference to other header files.

    itoa.h    - programming interface, header file
    itoa.c    - source file

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
## Features
- No need for a higher version of c++, c++11 can also be compiled
- There is no need for SSE instruction set optimization, and the performance of very large integers has increased by more than 30%
- The header file is separated from the source file, without too much inlining, preventing slow compilation

## illustrate
- Faster performance if inlined C++ version is required
- See C++ version for details[https://github.com/asciphx/FabCc/blob/lithium/fc/include/h/itoa.h](https://github.com/asciphx/FabCc/blob/lithium/fc/include/h/itoa.h)