#include <filesystem>
#include "xml.h"
#include "userdefinetype.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>

std::string DataDir = "XmlData/";

// 测试 int 类型的序列化与反序列化
TEST(XmlTest, IntSerialization)
{
    int original_int = 42;
    xml::serialize(original_int, "std_int", DataDir + "int_test.data");
    int deserialized_int = 0;
    xml::deserialize(deserialized_int, "std_int", DataDir + "int_test.data");
    ASSERT_EQ(original_int, deserialized_int);
}


int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directory(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

