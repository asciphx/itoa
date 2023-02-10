# itoa
宇宙中最快的整数到ASCII字符的转换。
它是用纯c语言编写的，仅一个头文件, 且没有引用其他头文件。

    itoa.h    - 编程接口
    itoa.c    - 数字查找表的定义

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
