/*
Both modules should at least support the serialization of
arithmetic types (see std::is_arithmetic),
C++ string type (std::string),
and STL containers (std::pair, std::vector, std::list, std::set, and std::map).
Both modules should provide a convenient mechanism (by macro, template, etc.) to support the serialization of user-defined types
[Bonus] Support the serialization of smart pointers, e.g., std::unique_ptr.
*/

#pragma once

#include <string>
#include <utility> // std::pair
#include <fstream>
#include <type_traits> // 添加此头文件以支持 std::enable_if 和 std::is_arithmetic
#include <list>
#include <vector>
#include <stdexcept> // std::runtime_error
#include <set>
#include <map>
#include <iostream>
#include <userdefinetype.h> // 添加此头文件以支持用户自定义类型的序列化
#include "macro.h"

namespace binary
{
   /**
    * @brief Write the is_arithmetic type to a binary file.
    * @tparam For arithmetic types, we can directly use sizeof(T) to get their size and write them to the file.
    */
   template <typename T>
   typename std::enable_if<std::is_arithmetic<T>::value, void>::type
   writeintofile(const T &t, std::ofstream &file)
   {
      // Write the data to the file
      file.write(reinterpret_cast<const char *>(&t), sizeof(T));
      if (!file)
      {
         throw std::runtime_error("Error writing to file");
      }
   }

   /**
    * @brief Read the is_arithmetic type from a binary file.
    * @tparam For arithmetic types, we can directly use sizeof(T) to get their size and read them from the file.
    */
   template <typename T>
   typename std::enable_if<std::is_arithmetic<T>::value, void>::type
   readfromfile(T &t, std::ifstream &file)
   {
      // Read the data from the file
      file.read(reinterpret_cast<char *>(&t), sizeof(T));
      if (!file)
      {
         throw std::runtime_error("Error reading from file");
      }
   }

   /**
    * @brief Write the std::string type to a binary file.
    * @tparam For std::string, we can use its size() method to get its size and write it to the file.
    * @tparam We first write its size, which is size_t type.
    */
   template <typename T>
   typename std::enable_if<std::is_same<T, std::string>::value, void>::type
   writeintofile(const T &t, std::ofstream &file)
   {
      /**
       * Write the data to the file
       * First write t's length
       * Then is t itself
       */
      size_t len = t.length();
      file.write(reinterpret_cast<const char *>(&len), sizeof(len));
      file.write(t.data(), len);
      if (!file)
      {
         throw std::runtime_error("Error writing to file");
      }
   }

   /**
    * @brief Read the std::string type from a binary file.
    * @tparam We read the length first, and then read the string itself
    */
   template <typename T>
   typename std::enable_if<std::is_same<T, std::string>::value, void>::type
   readfromfile(T &t, std::ifstream &file)
   {
      // read length first
      size_t len;
      file.read(reinterpret_cast<char *>(&len), sizeof(len));
      // resize the string to the length we read
      t.resize(len);
      // pay attention to the t.data(), it is read only before C++17
      file.read(&t[0], len); // 使用 &t[0] 以避免 const 问题
      if (!file)
      {
         throw std::runtime_error("Error reading from file");
      }
   }

   /**
    * @brief Write the std::pair type to a binary file.
    * @tparam 为 std::pair 类型专门提供序列化实现
    */
   template <typename T1, typename T2>
   void writeintofile(const std::pair<T1, T2> &t, std::ofstream &file)
   {
      // Write the first
      writeintofile(t.first, file);
      // Write the second
      writeintofile(t.second, file);
   }

   /**
    * @brief Read the std::pair type from a binary file.
    * @tparam 为 std::pair 类型专门提供反序列化实现
    */
   template <typename T1, typename T2>
   void readfromfile(std::pair<T1, T2> &t, std::ifstream &file)
   {
      // Read the first
      readfromfile(t.first, file);
      // Read the second
      readfromfile(t.second, file);
   }

   /**
    * @brief Write the std::vector type to a binary file.
    * @tparam 为 std::vector 类型专门提供序列化实现
    */
   template <typename T>
   void writeintofile(const std::vector<T> &t, std::ofstream &file)
   {
      // Write the size of the vector
      size_t size = t.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));
      for (const auto &item : t)
      {
         writeintofile(item, file);
      }
   }

   /**
    * @brief Read the std::vector type from a binary file.
    * @tparam 为 std::vector 类型专门提供反序列化实现
    */
   template <typename T>
   void readfromfile(std::vector<T> &t, std::ifstream &file)
   {
      // Read the size of the vector
      size_t size;
      file.read(reinterpret_cast<char *>(&size), sizeof(size));
      t.resize(size);
      for (auto &item : t)
      {
         readfromfile(item, file);
      }
   }

   /**
    * @brief Write the std::vector<bool> type to a binary file.
    * @tparam 为 std::vector<bool> 类型专门提供序列化实现
    */
   void writeintofile(const std::vector<bool> &t, std::ofstream &file)
   {
      // Write the size of the vector
      size_t size = t.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));
      for (size_t i = 0; i < size; ++i)
      {
         bool value = t[i];
         file.write(reinterpret_cast<const char *>(&value), sizeof(bool));
      }
   }
   /**
    * @brief Read the std::vector<bool> type from a binary file.
    * @tparam 为 std::vector<bool> 类型专门提供反序列化实现
    */
   void readfromfile(std::vector<bool> &t, std::ifstream &file)
   {
      // Read the size of the vector
      size_t size;
      file.read(reinterpret_cast<char *>(&size), sizeof(size));
      t.resize(size);
      for (size_t i = 0; i < size; ++i)
      {
         bool value;
         file.read(reinterpret_cast<char *>(&value), sizeof(bool));
         t[i] = value;
      }
   }

   /**
    * @brief Write the std::list type to a binary file.
    * @tparam 为 std::list 类型专门提供序列化实现
    */
   template <typename T>
   void writeintofile(const std::list<T> &t, std::ofstream &file)
   {
      // Write the size of the list
      size_t size = t.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));
      for (const auto &item : t)
      {
         writeintofile(item, file);
      }
   }
   /**
    * @brief Read the std::list type from a binary file.
    * @tparam 为 std::list 类型专门提供反序列化实现
    */
   template <typename T>
   void readfromfile(std::list<T> &t, std::ifstream &file)
   {
      // Read the size of the list
      size_t size;
      file.read(reinterpret_cast<char *>(&size), sizeof(size));
      t.resize(size);
      for (auto &item : t)
      {
         readfromfile(item, file);
      }
   }

   /**
    * @brief Write the std::set type to a binary file.
    * @tparam 为 std::set 类型专门提供序列化实现
    */
   template <typename T>
   void writeintofile(const std::set<T> &t, std::ofstream &file)
   {
      // Write the size of the set
      size_t size = t.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));
      for (const auto &item : t)
      {
         writeintofile(item, file);
      }
   }

   /**
    * @brief Read the std::set type from a binary file.
    * @tparam 为 std::set 类型专门提供反序列化实现
    */
   template <typename T>
   void readfromfile(std::set<T> &t, std::ifstream &file)
   {
      // Read the size of the set
      size_t size;
      file.read(reinterpret_cast<char *>(&size), sizeof(size));

      // 清空 set，然后读取元素并插入
      t.clear();
      for (size_t i = 0; i < size; ++i)
      {
         T item;
         readfromfile(item, file);
         t.insert(item);
      }
   }

   /**
    * @brief Write the std::map type to a binary file.
    * @tparam 为 std::map 类型专门提供序列化实现
    */
   template <typename K, typename V>
   void writeintofile(const std::map<K, V> &t, std::ofstream &file)
   {
      // Write the size of the map
      size_t size = t.size();
      file.write(reinterpret_cast<const char *>(&size), sizeof(size));
      for (const auto &item : t)
      {
         writeintofile(item.first, file);
         writeintofile(item.second, file);
      }
   }

   /**
    * @brief Read the std::map type from a binary file.
    * @tparam 为 std::map 类型专门提供反序列化实现
    */
   template <typename K, typename V>
   void readfromfile(std::map<K, V> &t, std::ifstream &file)
   {
      // Read the size of the map
      size_t size;
      file.read(reinterpret_cast<char *>(&size), sizeof(size));
      for (size_t i = 0; i < size; ++i)
      {
         K key;
         V value;
         readfromfile(key, file);
         readfromfile(value, file);
         t[key] = value;
      }
   }

   /**
    * @brief Write the user-defined type to a binary file.
    * @tparam 使用宏为用户自定义类型专门提供序列化实现
    */
   DEFINE_SERIALIZATION(userdefinetype::UserDefinedType,
      writeintofile(t.idx, file);
      writeintofile(t.name, file);
      writeintofile(t.data, file);,
      readfromfile(t.idx, file);
      readfromfile(t.name, file);
      readfromfile(t.data, file);)

   // serial and deserial function
   template <typename T>
   void serialize(const T &t, std::string filename)
   {
      std::ofstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for writing");
      }
      writeintofile(t, file);
      file.close();
   }

   template <typename T>
   void deserialize(T &t, std::string filename)
   {
      std::ifstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for reading");
      }
      readfromfile(t, file);
      file.close();
   }

}