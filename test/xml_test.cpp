#include <filesystem>
#include "xml.h"
#include "userdefinetype.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

std::string DataDir = "Data/XmlData/";

// 测试 int 类型的序列化与反序列化
TEST(XmlTest, IntSerialization)
{
    int original_int = 42;
    xml::serialize(original_int, "std_int", DataDir + "int_test.data");
    int deserialized_int = 0;
    xml::deserialize(deserialized_int, "std_int", DataDir + "int_test.data");
    ASSERT_EQ(original_int, deserialized_int);
}

// 测试 std::string 类型的序列化与反序列化
TEST(XmlTest, StringSerialization)
{
    std::string original_string = "Hello, World!";
    xml::serialize(original_string, "std_string", DataDir + "string_test.data");
    std::string deserialized_string;
    xml::deserialize(deserialized_string, "std_string", DataDir + "string_test.data");
    ASSERT_EQ(original_string, deserialized_string);
}

int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directories(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

