// 编写macro为用户提供自定义的序列化函数

#pragma once
#define DEFINE_SERIALIZATION(Type, WriteArgs, ReadArgs)                                           \
    void writeintofile(const Type &t, std::ofstream &file) \
    {                                                      \
        WriteArgs /* 展开 WriteArgs 参数包 */              \
    }                                                                                          \
    void readfromfile(Type &t, std::ifstream &file)        \
    {                                                      \
        ReadArgs /* 展开 ReadArgs 参数包 */                \
    }