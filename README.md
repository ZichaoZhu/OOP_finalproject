## 简介
这是我的OOP-Final-Project。

## 实现功能
目前这个Project实现了题目所要求的大部分功能。现做列举：
* binary
  * The serialization and deserialization of arithmetic types (see std::is_arithmetic)
  * The serialization and deserialization C++ string type (std::string),
  * The serialization and deserialization STL containers (std::pair, std::vector, std::list, std::set, and std::map).
  * Provide a convenient mechanism (by macro,) to support the serialization of user-defined types.
  * Support the serialization of smart pointers, e.g., std::unique_ptr.

* XML
  * The serialization and deserialization of arithmetic types (see std::is_arithmetic)
  * The serialization and deserialization C++ string type (std::string),
  * The serialization and deserialization STL containers (std::pair, std::vector, std::list, std::set, and std::map).
  * Provide a convenient mechanism (by macro,) to support the serialization of user-defined types.
  * Use binary-to-text encoding/decoding (base64) to implement a binary mode of XML serialization.
  * Support the serialization of smart pointers, e.g., std::unique_ptr.

## 文件说明
完整的文件夹结构如下：
```Shell
.
├── build
│   ├── bin
│   ├── cmake_install.cmake
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── compile_commands.json
│   ├── CTestTestfile.cmake
│   ├── external
│   ├── lib
│   ├── libbinary_lib.a
│   ├── Makefile
│   └── Testing
├── .vscode
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── CMakeLists.txt
├── Data
│   ├── BinaryData
│   └── XmlData
├── external
│   ├── googletest
│   └── tinyxml2
├── include
│   ├── binary.h
│   ├── macro.h
│   ├── userdefinetype.h
│   └── xml.h
├── README.md
├── src
│   ├── binary.cpp
│   └── xml.cpp
└── test
    ├── binary_test.cpp
    └── xml_test.cpp
```
我们来简要介绍以下各个文件夹：
1. build文件夹，用于保存生成可执行文件过程中保存的各种文件。
2. Data文件夹，用于保存可执行文件binary_test以及xml_test执行的过程中生成的各种数据文件。
3. external文件夹，用于保存第三方库，比如xml模块所用到的tinyxml2库，以及测试所用到的googletest库。
4. include文件夹，包含头文件binary.h以及xml.h。由于程序大多数函数都是使用模版的，因此几乎所有的主要代码都是写在这两个文件中的。
5. src文件夹，包含binary.cpp以及xml.cpp文件。由于上面的原因，这两个文件中实现的内容很少。xml.cpp中实现的主要是base64转换的一些函数。
6. .vscode文件夹，我在编写过程中所用到的文件夹，里面包含三个.json文件。其中，tasks.json文件中配置了几个任务：Build Project，用于编译；Run xml test，用于运行xml_test测试程序；Run binary test，用于运行binary_test测试程序。launch.json文件则实现了对binary以及xml部分的调试。
7. test文件夹，包含了我们的测试程序。

## 运行文件
我所提供的文件结构如下：
```Shell
.
├── CMakeLists.txt
├── external
│   ├── googletest
│   └── tinyxml2
├── .vscode
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── include
│   ├── binary.h
│   ├── macro.h
│   ├── userdefinetype.h
│   └── xml.h
├── README.md
├── src
│   ├── binary.cpp
│   └── xml.cpp
└── test
    ├── binary_test.cpp
    └── xml_test.cpp
```
这里有两种编译运行的方式，第一种是使用.vscode中的三个json文件，在vscode中运行任务。需要注意的是，在这种方式下，因为我的系统时macos，所以编译器是lldb。在不同平台上可能会编译失败。

第二种是使用命令行的方式，我们输入以下命令：
```txt
mkdir -p build
cd build
cmake ..
make
./bin/binary_test
./bin/xml_test
```
在第二种方式下，程序运行过程产生的数据文件夹Data位于build文件夹下。
*注：bin文件夹下可能会多出一个xmltest文件，那个是tinyxml2库提供的测试代码所编译出的结果*

## 测试说明
我们的测试代码包含了大部分的测试，比如所有std::is_arithmetic类型的测试，std::string的测试，所有STL容器的测试，用户自定义的变量的测试，三种智能指针的测试。特别的，我们测试了std::vector\<bool\>以及std::vector\<vector\<int\>\>这两个类型。
对于std::vector\<bool\>类型，我们发现了一个很有意思的地方。由于std::vector\<bool\> 是一个针对布尔值的特化版本，它并不存储 bool 类型的值，而是使用位压缩来存储布尔值。这导致 std::vector\<bool\> 的元素类型不是 bool，而是 std::__bit_const_reference 或类似的代理类型。因此迭代式的序列化对其并不起作用，于是我们编写了一个模版特化的版本，用于支持std::vector\<bool\> 的序列化与反序列化。

我们的测试结果如下所示：
```Shell
 ~/Desktop/OOP homework/Finalproject/build   main ±  ./bin/binary_test
[==========] Running 22 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 22 tests from BinaryTest
[ RUN      ] BinaryTest.IntSerialization
[       OK ] BinaryTest.IntSerialization (0 ms)
[ RUN      ] BinaryTest.FloatSerialization
[       OK ] BinaryTest.FloatSerialization (0 ms)
[ RUN      ] BinaryTest.DoubleSerialization
[       OK ] BinaryTest.DoubleSerialization (0 ms)
[ RUN      ] BinaryTest.CharSerialization
[       OK ] BinaryTest.CharSerialization (0 ms)
[ RUN      ] BinaryTest.BoolSerialization
[       OK ] BinaryTest.BoolSerialization (0 ms)
[ RUN      ] BinaryTest.CharConstSerialization
[       OK ] BinaryTest.CharConstSerialization (0 ms)
[ RUN      ] BinaryTest.IntConstSerialization
[       OK ] BinaryTest.IntConstSerialization (0 ms)
[ RUN      ] BinaryTest.StringSerialization
[       OK ] BinaryTest.StringSerialization (0 ms)
[ RUN      ] BinaryTest.PairSerialization
[       OK ] BinaryTest.PairSerialization (0 ms)
[ RUN      ] BinaryTest.VectorSerialization
[       OK ] BinaryTest.VectorSerialization (0 ms)
[ RUN      ] BinaryTest.VectorBoolSerialization
[       OK ] BinaryTest.VectorBoolSerialization (0 ms)
[ RUN      ] BinaryTest.VectorOfVectorSerialization
[       OK ] BinaryTest.VectorOfVectorSerialization (0 ms)
[ RUN      ] BinaryTest.ListSerialization
[       OK ] BinaryTest.ListSerialization (0 ms)
[ RUN      ] BinaryTest.ListBoolSerialization
[       OK ] BinaryTest.ListBoolSerialization (0 ms)
[ RUN      ] BinaryTest.SetSerialization
[       OK ] BinaryTest.SetSerialization (0 ms)
[ RUN      ] BinaryTest.SetBoolSerialization
[       OK ] BinaryTest.SetBoolSerialization (0 ms)
[ RUN      ] BinaryTest.MapSerialization
[       OK ] BinaryTest.MapSerialization (0 ms)
[ RUN      ] BinaryTest.MapBoolSerialization
[       OK ] BinaryTest.MapBoolSerialization (0 ms)
[ RUN      ] BinaryTest.UserDefinedTypeSerialization
[       OK ] BinaryTest.UserDefinedTypeSerialization (0 ms)
[ RUN      ] BinaryTest.UniquePtrSerialization
[       OK ] BinaryTest.UniquePtrSerialization (0 ms)
[ RUN      ] BinaryTest.SharedPtrSerialization
[       OK ] BinaryTest.SharedPtrSerialization (0 ms)
[ RUN      ] BinaryTest.WeakPtrSerialization
[       OK ] BinaryTest.WeakPtrSerialization (0 ms)
[----------] 22 tests from BinaryTest (6 ms total)

[----------] Global test environment tear-down
[==========] 22 tests from 1 test suite ran. (6 ms total)
[  PASSED  ] 22 tests.
```

```Shell
 ~/Desktop/OOP homework/Finalproject/build   main ±  ./bin/xml_test
[==========] Running 24 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 24 tests from XmlTest
[ RUN      ] XmlTest.IntSerialization
[       OK ] XmlTest.IntSerialization (0 ms)
[ RUN      ] XmlTest.FloatSerialization
[       OK ] XmlTest.FloatSerialization (0 ms)
[ RUN      ] XmlTest.DoubleSerialization
[       OK ] XmlTest.DoubleSerialization (0 ms)
[ RUN      ] XmlTest.CharSerialization
[       OK ] XmlTest.CharSerialization (0 ms)
[ RUN      ] XmlTest.BoolSerialization
[       OK ] XmlTest.BoolSerialization (0 ms)
[ RUN      ] XmlTest.CharConstSerialization
[       OK ] XmlTest.CharConstSerialization (0 ms)
[ RUN      ] XmlTest.IntConstSerialization
[       OK ] XmlTest.IntConstSerialization (0 ms)
[ RUN      ] XmlTest.StringSerialization
[       OK ] XmlTest.StringSerialization (0 ms)
[ RUN      ] XmlTest.PairSerialization
[       OK ] XmlTest.PairSerialization (0 ms)
[ RUN      ] XmlTest.PairBoolSerialization
[       OK ] XmlTest.PairBoolSerialization (0 ms)
[ RUN      ] XmlTest.VectorSerialization
[       OK ] XmlTest.VectorSerialization (0 ms)
[ RUN      ] XmlTest.VectorBoolSerialization
[       OK ] XmlTest.VectorBoolSerialization (0 ms)
[ RUN      ] XmlTest.VectorPairSerialization
[       OK ] XmlTest.VectorPairSerialization (0 ms)
[ RUN      ] XmlTest.ListSerialization
[       OK ] XmlTest.ListSerialization (0 ms)
[ RUN      ] XmlTest.ListBoolSerialization
[       OK ] XmlTest.ListBoolSerialization (0 ms)
[ RUN      ] XmlTest.SetSerialization
[       OK ] XmlTest.SetSerialization (0 ms)
[ RUN      ] XmlTest.SetBoolSerialization
[       OK ] XmlTest.SetBoolSerialization (0 ms)
[ RUN      ] XmlTest.MapSerialization
[       OK ] XmlTest.MapSerialization (0 ms)
[ RUN      ] XmlTest.MapBoolSerialization
[       OK ] XmlTest.MapBoolSerialization (0 ms)
[ RUN      ] XmlTest.UserDefinedTypeSerialization
[       OK ] XmlTest.UserDefinedTypeSerialization (0 ms)
[ RUN      ] XmlTest.BinarySerialization
[       OK ] XmlTest.BinarySerialization (0 ms)
[ RUN      ] XmlTest.UniquePtrSerialization
[       OK ] XmlTest.UniquePtrSerialization (0 ms)
[ RUN      ] XmlTest.WeakPtrSerialization
[       OK ] XmlTest.WeakPtrSerialization (0 ms)
[ RUN      ] XmlTest.SharedPtrSerialization
[       OK ] XmlTest.SharedPtrSerialization (0 ms)
[----------] 24 tests from XmlTest (7 ms total)

[----------] Global test environment tear-down
[==========] 24 tests from 1 test suite ran. (7 ms total)
[  PASSED  ] 24 tests.
```