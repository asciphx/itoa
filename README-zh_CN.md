# itoa
宇宙中最快的整数到ASCII字符的转换。支持C++11。
它是用纯c语言编写的，仅一个头文件, 且没有引用其他头文件。

    itoa.h    - 编程接口, 头文件
    itoa.c    - 源文件

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
- 无需高版本的c++, c++11也可以编译
- 无需SSE指令集优化, 在超大整数方面性能有30%以上的增幅
- 头文件与源文件分离, 无需过多的内联, 防止编译缓慢

## 说明
- 如果需要内联的C++版本, 性能会更快
- C++版本详见[https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h](https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h)