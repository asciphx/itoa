# itoa
宇宙中最快的整数到ASCII字符的转换。支持C++11。

    i2a.h    - 编程接口, c版本的头文件
    i2a.c    - c版本的源文件
    i2a.hpp  - C++版本的头文件

## 构建 (测试)
建议使用CMake进行源代码外构建。
```
mkdir build
cd build
cmake ..
cd ..
cmake --build ./build --config Release
./test

```
## 特征
- 无需高版本的c++, 性能会有约65%的提升
- 无需SSE指令集优化, 在超大整数方面性能有100%以上的增幅
- 头文件与源文件分离, 无需过多的内联, 防止编译缓慢

## 说明
- C++版本详见[https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h](https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h)

## 测试[test.c 文件, Linux]
c版本, 非内联(性能会稍微慢点) =>
- u64toa_sse2 use 1.289890 seconds
- u64toa use 2.110115 seconds
- u32toa_sse2 use 0.108332 seconds
- u2a use 0.125074 seconds

c++版本(大整数比SSE快112.3%, 整数比SSE快9.3%) =>
- u64toa_sse2 use 1.401212 seconds
- u64toa use 0.659776 seconds
- u32toa_sse2 use 0.106061 seconds
- u2a use 0.097243 seconds


## 详情(c++版本, Linux)
预测, 综合性能对比SSE大概如下

|Function |Time (ns)|Speedup|
|---------|--------:|------:|
|sse2     |    7.614| 25.51x|
|i2a      |    6.751| 28.55x|
|null     |    2.230| 87.09x|