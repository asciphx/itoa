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
- 如果需要内联的C++版本, 性能会有约65%的提升
- C++版本详见[https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h](https://gitee.com/ASCIPHX/FabCc/blob/lithium/fc/include/h/itoa.h)

## 测试[test.c 文件]
c版本, 非内联(性能会稍微慢点) =>
u64toa_sse2 use 1.282085 seconds
u64toa use 2.229963 seconds

u32toa_sse2 use 0.104293 seconds
u2a use 0.164470 seconds

c++版本(大整数比SSE快20.6%, 整数比SSE快3.4%) =>
u64toa_sse2 use 1.300226 seconds
u64toa use 1.078538 seconds

u32toa_sse2 use 0.103100 seconds
u2a use 0.099720 seconds

## 详情(c++版本)
预测, 综合性能对比SSE大概如下

|Function |Time (ns)|Speedup|
|---------|--------:|------:|
|sse2     |    7.614| 25.51x|
|i2a      |    7.051| 27.55x|
|null     |    2.230| 87.09x|