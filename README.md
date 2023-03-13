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
- If the inline C++ version is required, the performance will be improved by about 65%
- There is no need for SSE instruction set optimization, and the performance of very large integers has increased by more than 100%
- The header file is separated from the source file, without too much inlining, preventing slow compilation

## illustrate
- See C++ version for details[https://github.com/asciphx/FabCc/blob/lithium/fc/include/h/itoa.h](https://github.com/asciphx/FabCc/blob/lithium/fc/include/h/itoa.h)

## Test[test.c file, Linux]
c version, non-inline (performance will be slower) =>  
- u64toa_sse2 use 1.289890 seconds
- u64toa use 2.110115 seconds
- u32toa_sse2 use 0.108332 seconds
- u2a use 0.125074 seconds

c++ version (BigInt is 112.3% faster, Int is 9.3% faster) => 
- u64toa_sse2 use 1.401212 seconds
- u64toa use 0.659776 seconds
- u32toa_sse2 use 0.106061 seconds
- u2a use 0.097243 seconds

## Details (c++ version, Linux)
Prediction, comprehensive performance comparison with SSE is roughly as follows  

|Function |Time (ns)|Speedup|
|---------|--------:|------:|
|sse2     |    7.614| 25.51x|
|i2a      |    6.751| 28.55x|
|null     |    2.230| 87.09x|
