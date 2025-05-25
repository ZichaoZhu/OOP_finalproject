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

// 测试 float 类型的序列化与反序列化
TEST(BinaryTest, FloatSerialization)
{
    float original_float = 3.14f;
    binary::serialize(original_float, DataDir + "float_test.data");
    float deserialized_float = 0.0f;
    binary::deserialize(deserialized_float, DataDir + "float_test.data");
    ASSERT_EQ(original_float, deserialized_float);
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

// 测试 bool 类型的序列化与反序列化
TEST(BinaryTest, BoolSerialization)
{
    bool original_bool = true;
    binary::serialize(original_bool, DataDir + "bool_test.data");
    bool deserialized_bool = false;
    binary::deserialize(deserialized_bool, DataDir + "bool_test.data");
    ASSERT_EQ(original_bool, deserialized_bool);
}

// 测试 char const 类型的序列化与反序列化
TEST(BinaryTest, CharConstSerialization)
{
    const char original_char = 'B';
    binary::serialize(original_char, DataDir + "char_const_test.data");
    char deserialized_char = 0;
    binary::deserialize(deserialized_char, DataDir + "char_const_test.data");
    ASSERT_EQ(original_char, deserialized_char);
}

// 测试 int const 类型的序列化与反序列化
TEST(BinaryTest, IntConstSerialization)
{
    const int original_int = 100;
    binary::serialize(original_int, DataDir + "int_const_test.data");
    int deserialized_int = 0;
    binary::deserialize(deserialized_int, DataDir + "int_const_test.data");
    ASSERT_EQ(original_int, deserialized_int);
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

// 测试 std::vector<bool> 的序列化
TEST(BinaryTest, VectorBoolSerialization)
{
    std::vector<bool> original_vector_bool = {true, false, true, false};
    binary::serialize(original_vector_bool, DataDir + "vector_bool_test.data");
    
    std::vector<bool> deserialized_vector_bool;
    binary::deserialize(deserialized_vector_bool, DataDir + "vector_bool_test.data");
    
    ASSERT_EQ(original_vector_bool, deserialized_vector_bool);
}

// 测试 vector<vector<int>> 的序列化
TEST(BinaryTest, VectorOfVectorSerialization)
{
    std::vector<std::vector<int>> original_vector_of_vector = {{1, 2}, {3, 4}, {5, 6}};
    binary::serialize(original_vector_of_vector, DataDir + "vector_of_vector_test.data");
    
    std::vector<std::vector<int>> deserialized_vector_of_vector;
    binary::deserialize(deserialized_vector_of_vector, DataDir + "vector_of_vector_test.data");
    
    ASSERT_EQ(original_vector_of_vector, deserialized_vector_of_vector);
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

// 测试 std::list<bool> 的序列化
TEST(BinaryTest, ListBoolSerialization)
{
    std::list<bool> original_list_bool = {true, false, true, false};
    binary::serialize(original_list_bool, DataDir + "list_bool_test.data");
    
    std::list<bool> deserialized_list_bool;
    binary::deserialize(deserialized_list_bool, DataDir + "list_bool_test.data");
    
    ASSERT_EQ(original_list_bool, deserialized_list_bool);
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

// 测试 std::set<bool> 的序列化
TEST(BinaryTest, SetBoolSerialization)
{
    std::set<bool> original_set_bool = {true, false};
    binary::serialize(original_set_bool, DataDir + "set_bool_test.data");
    
    std::set<bool> deserialized_set_bool;
    binary::deserialize(deserialized_set_bool, DataDir + "set_bool_test.data");
    
    ASSERT_EQ(original_set_bool, deserialized_set_bool);
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

// 测试 std::map<bool, bool> 的序列化
TEST(BinaryTest, MapBoolSerialization)
{
    std::map<bool, bool> original_map_bool = {{true, false}, {false, true}};
    binary::serialize(original_map_bool, DataDir + "map_bool_test.data");
    
    std::map<bool, bool> deserialized_map_bool;
    binary::deserialize(deserialized_map_bool, DataDir + "map_bool_test.data");
    
    ASSERT_EQ(original_map_bool, deserialized_map_bool);
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

// 测试 std::unique_ptr 的序列化
TEST(BinaryTest, UniquePtrSerialization)
{
    std::unique_ptr<int> original_ptr = std::make_unique<int>(42);
    binary::serialize(original_ptr, DataDir + "unique_ptr_test.data");
    
    std::unique_ptr<int> deserialized_ptr;
    binary::deserialize(deserialized_ptr, DataDir + "unique_ptr_test.data");
    
    ASSERT_TRUE(deserialized_ptr != nullptr);
    ASSERT_EQ(*original_ptr, *deserialized_ptr);
}

// 测试 std::shared_ptr 的序列化
TEST(BinaryTest, SharedPtrSerialization)
{
    std::shared_ptr<int> original_ptr = std::make_shared<int>(42);
    binary::serialize(original_ptr, DataDir + "shared_ptr_test.data");
    
    std::shared_ptr<int> deserialized_ptr;
    binary::deserialize(deserialized_ptr, DataDir + "shared_ptr_test.data");
    
    ASSERT_TRUE(deserialized_ptr != nullptr);
    ASSERT_EQ(*original_ptr, *deserialized_ptr);
}

// 测试 std::weak_ptr 的序列化
TEST(BinaryTest, WeakPtrSerialization)
{
    std::shared_ptr<int> shared_ptr = std::make_shared<int>(42);
    std::weak_ptr<int> original_weak_ptr = shared_ptr;
    binary::serialize(original_weak_ptr, DataDir + "weak_ptr_test.data");
    
    std::weak_ptr<int> deserialized_weak_ptr;
    binary::deserialize(deserialized_weak_ptr, DataDir + "weak_ptr_test.data");
    
    ASSERT_TRUE(!deserialized_weak_ptr.expired());
    ASSERT_EQ(*shared_ptr, *deserialized_weak_ptr.lock());
}



int main(int argc, char **argv)
{
    std::filesystem::remove_all(DataDir);
    std::filesystem::create_directories(DataDir);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}