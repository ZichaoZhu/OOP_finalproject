#include <filesystem>
#include "binary.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

std::string DataDir = "Data/";

// 测试 int 类型的序列化与反序列化
TEST(BinaryTest, IntSerialization)
{
    int original_int = 42;
    binary::serialize(original_int, DataDir + "int_test.data");
    int deserialized_int = 0;
    binary::deserialize(deserialized_int, DataDir + "int_test.data");
    ASSERT_EQ(original_int, deserialized_int);
}

// 测试 double 类型的序列化与反序列化
TEST(BinaryTest, DoubleSerialization)
{
    double original_double = 3.14159;
    binary::serialize(original_double, DataDir + "double_test.data");
    double deserialized_double = 0.0;
    binary::deserialize(deserialized_double, DataDir + "double_test.data");
    ASSERT_EQ(original_double, deserialized_double);
}

// 测试 char 类型的序列化与反序列化
TEST(BinaryTest, CharSerialization)
{
    char original_char = 'A';
    binary::serialize(original_char, DataDir + "char_test.data");
    char deserialized_char = 0;
    binary::deserialize(deserialized_char, DataDir + "char_test.data");
    ASSERT_EQ(original_char, deserialized_char);
}

// 测试多个算术类型的组合
TEST(BinaryTest, MixedArithmeticSerialization)
{
    struct MixedData
    {
        int int_val;
        double double_val;
        char char_val;
    };

    MixedData original_data = {42, 3.14159, 'A'};
    binary::serialize(original_data.int_val, DataDir + "mixed_int_test.data");
    binary::serialize(original_data.double_val, DataDir + "mixed_double_test.data");
    binary::serialize(original_data.char_val, DataDir + "mixed_char_test.data");

    MixedData deserialized_data;
    binary::deserialize(deserialized_data.int_val, DataDir + "mixed_int_test.data");
    binary::deserialize(deserialized_data.double_val, DataDir + "mixed_double_test.data");
    binary::deserialize(deserialized_data.char_val, DataDir + "mixed_char_test.data");

    ASSERT_EQ(original_data.int_val, deserialized_data.int_val);
    ASSERT_EQ(original_data.double_val, deserialized_data.double_val);
    ASSERT_EQ(original_data.char_val, deserialized_data.char_val);
}

// 测试 std::string 的序列化
TEST(BinaryTest, StringSerialization)
{
    std::string original_string = "Hello, World.";
    binary::serialize(original_string, DataDir + "string_test.data");
    std::string deserialized_string;
    binary::deserialize(deserialized_string, DataDir + "string_test.data");

    ASSERT_EQ(original_string, deserialized_string);
}

int main(int argc, char **argv)
{
    std::filesystem::remove_all("Data");
    std::filesystem::create_directory("Data");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}