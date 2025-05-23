cmake_minimum_required(VERSION 3.10)
project(FinalProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加 include 文件夹到 include 路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加 Google Test
add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include)

# 添加 tinyxml2
add_subdirectory(external/tinyxml2)
include_directories(external/tinyxml2)

# 添加源文件
add_library(binary_lib src/binary.cpp)
target_link_libraries(binary_lib tinyxml2)

# 添加测试目标
add_executable(binary_test test/binary_test.cpp)
target_link_libraries(binary_test binary_lib gtest gtest_main pthread tinyxml2)

# 添加 XML 测试目标
add_executable(xml_test test/xml_test.cpp)
target_link_libraries(xml_test gtest gtest_main pthread tinyxml2)

# 启用测试
enable_testing()
add_test(NAME BinaryTest COMMAND binary_test)
add_test(NAME XmlTest COMMAND xml_test)