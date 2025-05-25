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

// 测试 float 类型的序列化与反序列化
TEST(XmlTest, FloatSerialization)
{
    float original_float = 3.14f;
    xml::serialize(original_float, "std_float", DataDir + "float_test.data");
    float deserialized_float = 0.0f;
    xml::deserialize(deserialized_float, "std_float", DataDir + "float_test.data");
    ASSERT_EQ(original_float, deserialized_float);
}

// 测试 double 类型的序列化与反序列化
TEST(XmlTest, DoubleSerialization)
{
    double original_double = 3.14159;
    xml::serialize(original_double, "std_double", DataDir + "double_test.data");
    double deserialized_double = 0.0;
    xml::deserialize(deserialized_double, "std_double", DataDir + "double_test.data");
    ASSERT_EQ(original_double, deserialized_double);
}

// 测试 char 类型的序列化与反序列化
TEST(XmlTest, CharSerialization)
{
    char original_char = 'A';
    xml::serialize(original_char, "std_char", DataDir + "char_test.data");
    char deserialized_char = 0;
    xml::deserialize(deserialized_char, "std_char", DataDir + "char_test.data");
    ASSERT_EQ(original_char, deserialized_char);
}

// 测试 bool 类型的序列化与反序列化
TEST(XmlTest, BoolSerialization)
{
    bool original_bool = true;
    xml::serialize(original_bool, "std_bool", DataDir + "bool_test.data");
    bool deserialized_bool;
    xml::deserialize(deserialized_bool, "std_bool", DataDir + "bool_test.data");
    ASSERT_EQ(original_bool, deserialized_bool);
}

// 测试 char const 类型的序列化与反序列化
TEST(XmlTest, CharConstSerialization)
{
    const char original_char = 'B';
    xml::serialize(original_char, "std_char_const", DataDir + "char_const_test.data");
    char deserialized_char = 0;
    xml::deserialize(deserialized_char, "std_char_const", DataDir + "char_const_test.data");
    ASSERT_EQ(original_char, deserialized_char);
}

// 测试 int const 类型的序列化与反序列化
TEST(XmlTest, IntConstSerialization)
{
    const int original_int = 100;
    xml::serialize(original_int, "std_int_const", DataDir + "int_const_test.data");
    int deserialized_int = 0;
    xml::deserialize(deserialized_int, "std_int_const", DataDir + "int_const_test.data");
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

// 测试 std::pair 类型的序列化与反序列化
TEST(XmlTest, PairSerialization)
{
    std::pair<int, std::string> original_pair(1, "Hello, world.");
    xml::serialize(original_pair, "std_pair", DataDir + "pair_test.data");
    
    std::pair<int, std::string> deserialized_pair;
    xml::deserialize(deserialized_pair, "std_pair", DataDir + "pair_test.data");
    ASSERT_EQ(original_pair, deserialized_pair);
}

// 测试 std::pair<bool, std::string> 类型的序列化与反序列化
TEST(XmlTest, PairBoolSerialization)
{
    std::pair<bool, std::string> original_pair_bool(true, "Hello, world.");
    xml::serialize(original_pair_bool, "std_pair_bool", DataDir + "pair_bool_test.data");
    
    std::pair<bool, std::string> deserialized_pair_bool;
    xml::deserialize(deserialized_pair_bool, "std_pair_bool", DataDir + "pair_bool_test.data");
    
    ASSERT_EQ(original_pair_bool, deserialized_pair_bool);
}

// 测试 std::vector 类型的序列化与反序列化
TEST(XmlTest, VectorSerialization)
{
    std::vector<int> original_vector = {4, 5, 6, 7, 8};
    xml::serialize(original_vector, "std_vector", DataDir + "vector_test.data");
    
    std::vector<int> deserialized_vector;
    xml::deserialize(deserialized_vector, "std_vector", DataDir + "vector_test.data");
    
    ASSERT_EQ(original_vector, deserialized_vector);
}

// 测试 std::vector<bool> 类型的序列化与反序列化
TEST(XmlTest, VectorBoolSerialization)
{
    std::vector<bool> original_vector_bool = {true, false, true, false};
    xml::serialize(original_vector_bool, "std_vector_bool", DataDir + "vector_bool_test.data");
    
    std::vector<bool> deserialized_vector_bool;
    xml::deserialize(deserialized_vector_bool, "std_vector_bool", DataDir + "vector_bool_test.data");
    
    ASSERT_EQ(original_vector_bool, deserialized_vector_bool);
}

// 测试 std::vector<std::pair<int, std::string>> 类型的序列化与反序列化
TEST(XmlTest, VectorPairSerialization)
{
    std::vector<std::pair<int, std::string>> original_vector_pair = {{1, "one"}, {2, "two"}, {3, "three"}};
    xml::serialize(original_vector_pair, "std_vector_pair", DataDir + "vector_pair_test.data");
    
    std::vector<std::pair<int, std::string>> deserialized_vector_pair;
    xml::deserialize(deserialized_vector_pair, "std_vector_pair", DataDir + "vector_pair_test.data");
    
    ASSERT_EQ(original_vector_pair, deserialized_vector_pair);
}

// 测试 std::list 类型的序列化与反序列化
TEST(XmlTest, ListSerialization)
{
    std::list<int> original_list = {1, 2, 3, 4, 5};
    xml::serialize(original_list, "std_list", DataDir + "list_test.data");
    
    std::list<int> deserialized_list;
    xml::deserialize(deserialized_list, "std_list", DataDir + "list_test.data");
    
    ASSERT_EQ(original_list, deserialized_list);
}

// 测试 std::list<bool> 类型的序列化与反序列化
TEST(XmlTest, ListBoolSerialization)
{
    std::list<bool> original_list_bool = {true, false, true, false};
    xml::serialize(original_list_bool, "std_list_bool", DataDir + "list_bool_test.data");
    
    std::list<bool> deserialized_list_bool;
    xml::deserialize(deserialized_list_bool, "std_list_bool", DataDir + "list_bool_test.data");
    
    ASSERT_EQ(original_list_bool, deserialized_list_bool);
}

// 测试 std::set 类型的序列化与反序列化
TEST(XmlTest, SetSerialization)
{
    std::set<int> original_set = {1, 2, 3, 4, 5};
    xml::serialize(original_set, "std_set", DataDir + "set_test.data");
    
    std::set<int> deserialized_set;
    xml::deserialize(deserialized_set, "std_set", DataDir + "set_test.data");
    
    ASSERT_EQ(original_set, deserialized_set);
}

// 测试 std::set<bool> 类型的序列化与反序列化
TEST(XmlTest, SetBoolSerialization)
{
    std::set<bool> original_set_bool = {true, false};
    xml::serialize(original_set_bool, "std_set_bool", DataDir + "set_bool_test.data");
    
    std::set<bool> deserialized_set_bool;
    xml::deserialize(deserialized_set_bool, "std_set_bool", DataDir + "set_bool_test.data");
    
    ASSERT_EQ(original_set_bool, deserialized_set_bool);
}

// 测试 std::map 类型的序列化与反序列化
TEST(XmlTest, MapSerialization)
{
    std::map<int, std::string> original_map = {{1, "one"}, {2, "two"}, {3, "three"}};
    xml::serialize(original_map, "std_map", DataDir + "map_test.data");
    
    std::map<int, std::string> deserialized_map;
    xml::deserialize(deserialized_map, "std_map", DataDir + "map_test.data");
    
    ASSERT_EQ(original_map, deserialized_map);
}

// 测试 std::map<bool, std::string> 类型的序列化与反序列化
TEST(XmlTest, MapBoolSerialization)
{
    std::map<bool, std::string> original_map_bool = {{true, "true"}, {false, "false"}};
    xml::serialize(original_map_bool, "std_map_bool", DataDir + "map_bool_test.data");
    
    std::map<bool, std::string> deserialized_map_bool;
    xml::deserialize(deserialized_map_bool, "std_map_bool", DataDir + "map_bool_test.data");
    
    ASSERT_EQ(original_map_bool, deserialized_map_bool);
}

// 测试用户自定义类型的序列化与反序列化
TEST(XmlTest, UserDefinedTypeSerialization)
{
    userdefinetype::UserDefinedType original_user_defined;
    userdefinetype::set(original_user_defined, 1, "test", {2.0, 3.0, 4.5});
    
    xml::serialize(original_user_defined, "user_defined", DataDir + "user_defined_test.data");
    
    userdefinetype::UserDefinedType deserialized_user_defined;
    xml::deserialize(deserialized_user_defined, "user_defined", DataDir + "user_defined_test.data");
    
    ASSERT_EQ(original_user_defined.idx, deserialized_user_defined.idx);
    ASSERT_EQ(original_user_defined.name, deserialized_user_defined.name);
    ASSERT_EQ(original_user_defined.data, deserialized_user_defined.data);
}

// 测试二进制类型的序列化与反序列化
TEST(XmlTest, BinarySerialization)
{
    std::vector<uint8_t> original_binary = {0x01, 0x02, 0x03, 0x04, 0x05};
    xml::serialize(original_binary, "std_binary", DataDir + "binary_test.data");
    
    std::vector<uint8_t> deserialized_binary;
    xml::deserialize(deserialized_binary, "std_binary", DataDir + "binary_test.data");
    
    ASSERT_EQ(original_binary, deserialized_binary);
}

int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directories(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

