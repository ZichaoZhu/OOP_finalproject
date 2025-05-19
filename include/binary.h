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
#include <fstream>

namespace binary
{
   /**
    * @brief Serialize the is_arithmetic type to a binary file.
    * @tparam For arithmetic types, we can directly use sizeof(T) to get their size and write them to the file.
    */
   template <typename T>
   typename std::enable_if<std::is_arithmetic<T>::value, void>::type
   serialize(const T &t, std::string filename)
   {
      // Open the file in binary mode
      std::ofstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for writing");
      }
      // Write the data to the file
      file.write(reinterpret_cast<const char *>(&t), sizeof(T));
      if (!file)
      {
         throw std::runtime_error("Error writing to file");
      }
      // Close the file
      file.close();
   }

   /**
    * @brief Deserialize the is_arithmetic type from a binary file.
    * @tparam For arithmetic types, we can directly use sizeof(T) to get their size and read them from the file.
    */
   template <typename T>
   typename std::enable_if<std::is_arithmetic<T>::value, void>::type
   deserialize(T &t, std::string filename)
   {
      // Open the file in binary mode
      std::ifstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for reading");
      }
      // Read the data from the file
      file.read(reinterpret_cast<char *>(&t), sizeof(T));
      if (!file)
      {
         throw std::runtime_error("Error reading from file");
      }
      // Close the file
      file.close();
   }

   /**
    * @brief Serialize the std::string type to a binary file.
    * @tparam For std::string, we can use its size() method to get its size and write it to the file.
    * @tparam We first write its size, which is size_t type.
    */
   template <typename T>
   typename std::enable_if<std::is_same<T, std::string>::value, void>::type
   serialize(const T &t, std::string filename)
   {
      // Open the file in binary mode
      std::ofstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for writing");
      }
      /**
       * Write the data to the file
       * First write t's length
       * Then is t itself
       */
      size_t len = t.length();
      file.write(reinterpret_cast<char *>(&len), sizeof(len));
      file.write(t.data(), len);
      if (!file)
      {
         throw std::runtime_error("Error writing to file");
      }
      // Close the file
      file.close();
   }

   /**
    * @brief Deserialize the std::string type from a binary file.
    * @tparam We read the length first, and then read the string itself
    */
   template <typename T>
   typename std::enable_if<std::is_same<T, std::string>::value, void>::type
   deserialize(T &t, std::string filename)
   {
      std::ifstream file(filename, std::ios::binary);
      if (!file)
      {
         throw std::runtime_error("Could not open file for reading");
      }
      // read length first
      size_t len;
      file.read(reinterpret_cast<char *>(&len), sizeof(len));
      // resize the string to the length we read
      t.resize(len);
      // pay attention to the t.data(), it is read only before C++17
      file.read(t.data(), len);
      if (!file)
      {
         throw std::runtime_error("Error reading from file");
      }
      file.close();
   }
}