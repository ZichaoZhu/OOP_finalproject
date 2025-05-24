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

// 测试 std::pair 类型的序列化与反序列化
TEST(XmlTest, PairSerialization)
{
    std::pair<int, std::string> original_pair(1, "Hello, world.");
    xml::serialize(original_pair, "std_pair", DataDir + "pair_test.data");
    
    std::pair<int, std::string> deserialized_pair;
    xml::deserialize(deserialized_pair, "std_pair", DataDir + "pair_test.data");
    ASSERT_EQ(original_pair, deserialized_pair);
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

// 测试 std::list 类型的序列化与反序列化
TEST(XmlTest, ListSerialization)
{
    std::list<int> original_list = {1, 2, 3, 4, 5};
    xml::serialize(original_list, "std_list", DataDir + "list_test.data");
    
    std::list<int> deserialized_list;
    xml::deserialize(deserialized_list, "std_list", DataDir + "list_test.data");
    
    ASSERT_EQ(original_list, deserialized_list);
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

int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directories(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

