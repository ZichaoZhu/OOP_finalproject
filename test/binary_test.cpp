#include <filesystem>
#include "binary.h"
#include "userdefinetype.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>

std::string DataDir = "Data/BinaryData/";

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

// 测试 std::pair 的序列化
TEST(BinaryTest, PairSerialization)
{
    std::pair<int, std::string> original_pair(1, "Hello, world.");
    binary::serialize(original_pair, DataDir + "pair_test.data");
    
    std::pair<int, std::string> deserialized_pair;
    binary::deserialize(deserialized_pair, DataDir + "pair_test.data");
    ASSERT_EQ(original_pair, deserialized_pair);
}

// 测试 std::vector 的序列化
TEST(BinaryTest, VectorSerialization)
{
    std::vector<int> original_vector = {1, 2, 3, 4, 5};
    binary::serialize(original_vector, DataDir + "vector_test.data");
    
    std::vector<int> deserialized_vector;
    binary::deserialize(deserialized_vector, DataDir + "vector_test.data");
    
    ASSERT_EQ(original_vector, deserialized_vector);
}

// 测试 std::list 的序列化
TEST(BinaryTest, ListSerialization)
{
    std::list<int> original_list = {1, 2, 3, 4, 5};
    binary::serialize(original_list, DataDir + "list_test.data");
    
    std::list<int> deserialized_list;
    binary::deserialize(deserialized_list, DataDir + "list_test.data");
    
    ASSERT_EQ(original_list, deserialized_list);
}

// 测试 std::set 的序列化
TEST(BinaryTest, SetSerialization)
{
    std::set<int> original_set = {1, 2, 3, 4, 5};
    binary::serialize(original_set, DataDir + "set_test.data");
    
    std::set<int> deserialized_set;
    binary::deserialize(deserialized_set, DataDir + "set_test.data");
    
    ASSERT_EQ(original_set, deserialized_set);
}

// 测试 std::map 的序列化
TEST(BinaryTest, MapSerialization)
{
    std::map<int, std::string> original_map = {{1, "one"}, {2, "two"}, {3, "three"}};
    binary::serialize(original_map, DataDir + "map_test.data");
    
    std::map<int, std::string> deserialized_map;
    binary::deserialize(deserialized_map, DataDir + "map_test.data");
    
    ASSERT_EQ(original_map, deserialized_map);
}

// 测试自定义类型的序列化
TEST(BinaryTest, UserDefinedTypeSerialization)
{
    int idx = 1;
    std::string name = "Liu Bei";
    std::vector<double> data = {1.0, 2.0, 3.0};
    userdefinetype::UserDefinedType original_data;
    userdefinetype::set(original_data, idx, name, data);
    binary::serialize(original_data, DataDir + "user_defined_test.data");
    
    userdefinetype::UserDefinedType deserialized_data;
    binary::deserialize(deserialized_data, DataDir + "user_defined_test.data");
    
    ASSERT_EQ(original_data.idx, deserialized_data.idx);
    ASSERT_EQ(original_data.name, deserialized_data.name);
    ASSERT_EQ(original_data.data, deserialized_data.data);
}



int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directories(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}