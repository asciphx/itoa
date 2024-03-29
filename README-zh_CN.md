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
- 无需高版本的c++, 性能会有约100%的提升
- 头文件与源文件分离, 无需过多的内联, 防止编译缓慢
- ![测试](./test.jpg)

## 说明
- C++版本详见[https://gitee.com/asciphx/Nod/blob/main/fc/include/hpp/i2a.hpp](https://gitee.com/asciphx/Nod/blob/main/fc/include/hpp/i2a.hpp)

## 详情(c++版本, Linux)
预测, 综合性能对比SSE大概如下

|Function |Time (ns)|Speedup|
|---------|--------:|------:|
|sse2     |    7.614| 25.51x|
|i2a      |    3.685| 53.15x|
|null     |    2.230| 87.09x|