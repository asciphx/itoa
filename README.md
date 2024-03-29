# itoa
Universe's fastest integer to ASCII conversion. C++11 is supported.

    i2a.h    - programming interface, header file for c version
    i2a.c    - source file for the c version
    i2a.hpp  - C++ version header file

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
- If the inline C++ version is required, the performance will be improved by about 100%
- The header file is separated from the source file, without too much inlining, preventing slow compilation
- ![test](./test.jpg)

## illustrate
- See C++ version for details[https://github.com/asciphx/Nod/blob/main/fc/include/hpp/i2a.hpp](https://github.com/asciphx/Nod/blob/main/fc/include/hpp/i2a.hpp)

## Details (c++ version, Linux)
Prediction, comprehensive performance comparison with SSE is roughly as follows  

|Function |Time (ns)|Speedup|
|---------|--------:|------:|
|sse2     |    7.614| 25.51x|
|i2a      |    3.685| 53.15x|
|null     |    2.230| 87.09x|
