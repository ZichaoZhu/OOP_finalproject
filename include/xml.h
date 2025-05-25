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
#include <vector>
#include <utility> // std::pair
#include <list>
#include <set>
#include <map>
#include <type_traits>
#include "tinyxml2.h"
#include <iostream>
#include "userdefinetype.h" // 添加此头文件以支持用户自定义类型的序列化

namespace xml
{
    /**
     * @brief Write the is-arithmetic type to XML.
     * @tparam Write as this format: <val = "...">
     */
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, void>::type
    writeintoXML(const T &t, tinyxml2::XMLElement &Eletype)
    {
        // Create a new element for the value
        tinyxml2::XMLElement *Eleval = Eletype.GetDocument()->NewElement("value");
        Eleval->SetAttribute("val", t);
        Eletype.InsertEndChild(Eleval);
    }

    /**
     * @brief Read the is-arithmetic type from XML.
     * @tparam Read as this format: <val = "...">
     */
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, void>::type
    readfromXML(T &t, tinyxml2::XMLElement &Eletype)
    {
        // Get the value element
        tinyxml2::XMLElement *Eleval = Eletype.FirstChildElement("value");
        if (Eleval)
        {
            // Get the value attribute
            const char *val = Eleval->Attribute("val");
            if (val)
            {
                // Due with the bool type 
                if (typeid(T) == typeid(bool)) t = strcmp(val, "true") == 0;           
                else t = static_cast<T>(std::atof(val));
            }
        }
    }

    /**
     * @brief Write the std::string type to XML.
     * @tparam Write as this format: <val = "...">
     */
    template <typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, void>::type
    writeintoXML(const T &t, tinyxml2::XMLElement &Eletype)
    {
        // Create a new element for the value
        tinyxml2::XMLElement *Eleval = Eletype.GetDocument()->NewElement("value");
        Eleval->SetAttribute("val", t.c_str());
        Eletype.InsertEndChild(Eleval);
    }

    /**
     * @brief Read the std::string type from XML.
     * @tparam Read as this format: <val = "...">
     */
    template <typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, void>::type
    readfromXML(T &t, tinyxml2::XMLElement &Eletype)
    {
        // Get the value element
        tinyxml2::XMLElement *Eleval = Eletype.FirstChildElement("value");
        if (Eleval)
        {
            // Get the value attribute
            const char *val = Eleval->Attribute("val");
            if (val)
            {
                t = std::string(val);
            }
        }
    }

    /**
     * @brief Write the std::pair type to XML.
     * @tparam Write as this format: <first>
     *                                  <value val = "...">
     *                               </first>
     *                               <second>
     *                                  <value val = "...">
     *                               </second>
     */
    template <typename T1, typename T2>
    void writeintoXML(const std::pair<T1, T2> &t, tinyxml2::XMLElement &Eletype)
    {
        // Create a new element for the first value
        tinyxml2::XMLElement *Elefirst = Eletype.GetDocument()->NewElement("first");
        writeintoXML(t.first, *Elefirst);
        Eletype.InsertEndChild(Elefirst);

        // Create a new element for the second value
        tinyxml2::XMLElement *Elesecond = Eletype.GetDocument()->NewElement("second");
        writeintoXML(t.second, *Elesecond);
        Eletype.InsertEndChild(Elesecond);
    }

    /**
     * @brief Read the std::pair type from XML.
     * @tparam Read as this format: <first>
     *                                  <value val = "...">
     *                               </first>
     *                               <second>
     *                                  <value val = "...">
     *                               </second>
     */
    template <typename T1, typename T2>
    void readfromXML(std::pair<T1, T2> &t, tinyxml2::XMLElement &Eletype)
    {
        // Get the first element
        tinyxml2::XMLElement *Elefirst = Eletype.FirstChildElement("first");
        if (Elefirst)
        {
            readfromXML(t.first, *Elefirst);
        }

        // Get the second element
        tinyxml2::XMLElement *Elesecond = Eletype.FirstChildElement("second");
        if (Elesecond)
        {
            readfromXML(t.second, *Elesecond);
        }
    }

    /**
     * @brief Write the std::vector type to XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void writeintoXML(const std::vector<T> &t, tinyxml2::XMLElement &Eletype)
    {
        // Write each element in the vector
        for (const auto &item : t)
        {
            // Create a new element for the vector
            tinyxml2::XMLElement *Elevector = Eletype.GetDocument()->NewElement("element");
            writeintoXML(item, *Elevector);
            Eletype.InsertEndChild(Elevector);
        }
    }

    /**
     * @brief Read the std::vector type from XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void readfromXML(std::vector<T> &t, tinyxml2::XMLElement &Eletype)
    {
        tinyxml2::XMLElement *Elevector = Eletype.FirstChildElement("element");
        while (Elevector)
        {
            T item;
            readfromXML(item, *Elevector);
            t.push_back(item);
            Elevector = Elevector->NextSiblingElement("element");
        }
    }

    /**
     * @brief Write the std::vector<bool> type to XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    void writeintoXML(const std::vector<bool> &t, tinyxml2::XMLElement &Eletype)
    {
        for (size_t i = 0; i < t.size(); ++i)
        {
            tinyxml2::XMLElement *EleBool = Eletype.GetDocument()->NewElement("element");
            EleBool->SetAttribute("val", t[i] ? "true" : "false");
            Eletype.InsertEndChild(EleBool);
        }
    }
    /**
     * @brief Read the std::vector<bool> type from XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    void readfromXML(std::vector<bool> &t, tinyxml2::XMLElement &Eletype)
    {
        tinyxml2::XMLElement *EleBool = Eletype.FirstChildElement("element");
        while (EleBool)
        {
            const char *val = EleBool->Attribute("val");
            if (val)
            {
                t.push_back(strcmp(val, "true") == 0);
            }
            EleBool = EleBool->NextSiblingElement("element");
        }
    }

    /**
     * @brief Write the std::list type to XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void writeintoXML(const std::list<T> &t, tinyxml2::XMLElement &Eletype)
    {
        // Write each element in the list
        for (const auto &item : t)
        {
            // Create a new element for the list
            tinyxml2::XMLElement *Elelist = Eletype.GetDocument()->NewElement("element");
            writeintoXML(item, *Elelist);
            Eletype.InsertEndChild(Elelist);
        }
    }

    /**
     * @brief Read the std::list type from XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void readfromXML(std::list<T> &t, tinyxml2::XMLElement &Eletype)
    {
        tinyxml2::XMLElement *Elelist = Eletype.FirstChildElement("element");
        while (Elelist)
        {
            T item;
            readfromXML(item, *Elelist);
            t.push_back(item);
            Elelist = Elelist->NextSiblingElement("element");
        }
    }

    /**
     * @brief Write the std::set type to XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void writeintoXML(const std::set<T> &t, tinyxml2::XMLElement &Eletype)
    {
        // Write each element in the set
        for (const auto &item : t)
        {
            // Create a new element for the set
            tinyxml2::XMLElement *Eleset = Eletype.GetDocument()->NewElement("element");
            writeintoXML(item, *Eleset);
            Eletype.InsertEndChild(Eleset);
        }
    }
    /**
     * @brief Read the std::set type from XML.
     * @tparam Write as this format: <element>
     *                                  <value val = "...">
     *                                </element>
     *                                <element>
     *                                  <value val = "...">
     *                                </element>
     *                                  ...
     */
    template <typename T>
    void readfromXML(std::set<T> &t, tinyxml2::XMLElement &Eletype)
    {
        tinyxml2::XMLElement *Eleset = Eletype.FirstChildElement("element");
        while (Eleset)
        {
            T item;
            readfromXML(item, *Eleset);
            t.insert(item);
            Eleset = Eleset->NextSiblingElement("element");
        }
    }

    /**
     * @brief Write the std::map type to XML.
     * @tparam Write as this format: <element>
     *                                  <key>
     *                                      <value val=.../>
     *                                  </key>
     *                                  <value>
     *                                      <value val=.../>
     *                                  </value>
     *                               </element>
     *                        ...
     */
    template <typename K, typename V>
    void writeintoXML(const std::map<K, V> &t, tinyxml2::XMLElement &Eletype)
    {
        // Write each element in the map
        for (const auto &item : t)
        {
            // Create a new element for the map
            tinyxml2::XMLElement *Elemap = Eletype.GetDocument()->NewElement("element");

            // Create and add key element
            tinyxml2::XMLElement *Elekey = Elemap->GetDocument()->NewElement("key");
            writeintoXML(item.first, *Elekey);
            Elemap->InsertEndChild(Elekey);

            // Create and add value element
            tinyxml2::XMLElement *Elevalue = Elemap->GetDocument()->NewElement("value");
            writeintoXML(item.second, *Elevalue);
            Elemap->InsertEndChild(Elevalue);

            Eletype.InsertEndChild(Elemap);
        }
    }
    /**
     * @brief Read the std::map type from XML.
     * @tparam Write as this format: <element>
     *                                  <key>
     *                                      <value val=.../>
     *                                  </key>
     *                                  <value>
     *                                      <value val=.../>
     *                                  </value>
     *                               </element>
     *                        ...
     */
    template <typename K, typename V>
    void readfromXML(std::map<K, V> &t, tinyxml2::XMLElement &Eletype)
    {
        tinyxml2::XMLElement *Elemap = Eletype.FirstChildElement("element");
        while (Elemap)
        {
            K key;
            tinyxml2::XMLElement *Elekey = Elemap->FirstChildElement("key");
            if (Elekey)
            {
                readfromXML(key, *Elekey);
            }

            V value;
            tinyxml2::XMLElement *Elevalue = Elemap->FirstChildElement("value");
            if (Elevalue)
            {
                readfromXML(value, *Elevalue);
            }

            t[key] = value;
            Elemap = Elemap->NextSiblingElement("element");
        }
    }

    /**
     * @brief Serialize and deserialize the user-defined type.
     * @tparam Write as this format: <element>
     *                                  <value val=.../>
     *                               </element>
     */
    void writeintoXML(const userdefinetype::UserDefinedType &t, tinyxml2::XMLElement &Eletype)
    {
        // 序列化 idx
        tinyxml2::XMLElement *EleIdx = Eletype.GetDocument()->NewElement("element");
        writeintoXML(t.idx, *EleIdx);
        Eletype.InsertEndChild(EleIdx);

        // 序列化 name
        tinyxml2::XMLElement *EleName = Eletype.GetDocument()->NewElement("element");
        writeintoXML(t.name, *EleName);
        Eletype.InsertEndChild(EleName);

        // 序列化 data
        tinyxml2::XMLElement *EleData = Eletype.GetDocument()->NewElement("element");
        writeintoXML(t.data, *EleData);
        Eletype.InsertEndChild(EleData);
    }

    void readfromXML(userdefinetype::UserDefinedType &t, tinyxml2::XMLElement &Eletype)
    {
        // 反序列化 idx
        tinyxml2::XMLElement *EleIdx = Eletype.FirstChildElement("element");
        if (EleIdx)
        {
            readfromXML(t.idx, *EleIdx);
            EleIdx = EleIdx->NextSiblingElement("element");
        }

        // 反序列化 name
        if (EleIdx)
        {
            readfromXML(t.name, *EleIdx);
            EleIdx = EleIdx->NextSiblingElement("element");
        }

        // 反序列化 data
        if (EleIdx)
        {
            readfromXML(t.data, *EleIdx);
            EleIdx = EleIdx->NextSiblingElement("element");
        }
    }

    /**
     * @brief Write the unique_ptr type.
     * @tparam Write as this format:<value val=.../>                                                          
     */
    template <typename T>
    void writeintoXML(const std::unique_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        if (ptr)
        {
            writeintoXML(*ptr, Eletype);
        }
    }

    /**
     * @brief Read the unique_ptr type.
     * @tparam Read as this format:<value val=.../>                                                          
     */
    template <typename T>
    void readfromXML(std::unique_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        ptr = std::make_unique<T>();
        readfromXML(*ptr, Eletype);
    }

    /**
     * @brief Read the shared_ptr type.
     * @tparam Read as this format:<value val=.../>                                                          
     */
    template <typename T>
    void writeintoXML(const std::shared_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        if (ptr)
        {
            writeintoXML(*ptr, Eletype);
        }
    }
    /**
     * @brief Read the shared_ptr type.
     * @tparam Read as this format:<value val=.../>                                                          
     */
    template <typename T>
    void readfromXML(std::shared_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        ptr = std::make_shared<T>();
        readfromXML(*ptr, Eletype);
    }

    /**
     * @brief Write the weak_ptr type.
     * @tparam Write as this format:<value val=.../>                                                          
     */
    template <typename T>
    void writeintoXML(const std::weak_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        if (auto sharedPtr = ptr.lock())
        {
            writeintoXML(*sharedPtr, Eletype);
        }
    }

    /**
     * @brief Read the weak_ptr type.
     * @tparam Read as this format:<value val=.../>                                                          
     */
    template <typename T>
    void readfromXML(std::weak_ptr<T> &ptr, tinyxml2::XMLElement &Eletype)
    {
        // Create a shared_ptr to hold the deserialized object
        static std::shared_ptr<T> sharedPtr = std::make_shared<T>();
        readfromXML(*sharedPtr, Eletype);
        ptr = sharedPtr;
    }

    template <typename T>
    void serialize(const T &t, std::string nameoftype, std::string filename)
    {
        // Create a new XML document
        tinyxml2::XMLDocument doc;

        // Create a root element
        tinyxml2::XMLElement *root = doc.NewElement("serialization");
        doc.InsertFirstChild(root);

        // Create a new element for the type
        tinyxml2::XMLElement *Eletype = doc.NewElement(nameoftype.c_str());
        root->InsertEndChild(Eletype);

        // Serialize the object into XML
        writeintoXML(t, *Eletype); // 解引用指针

        doc.SaveFile(filename.c_str());
    }

    template <typename T>
    void deserialize(T &t, std::string nameoftype, std::string filename)
    {
        // Create a new XML document
        tinyxml2::XMLDocument doc;

        // Load the XML document
        doc.LoadFile(filename.c_str());

        // Get the root element
        tinyxml2::XMLElement *root = doc.RootElement();

        // Get the type element
        tinyxml2::XMLElement *Eletype = root->FirstChildElement(nameoftype.c_str());

        readfromXML(t, *Eletype); // 解引用指针
    }

    // Base64 编码函数
    std::string base64Encode(const std::vector<uint8_t> &data);

    // Base64 解码函数
    std::vector<uint8_t> base64Decode(const std::string &encoded);

    // 针对二进制数据的序列化
    void writeintoXML(const std::vector<uint8_t> &binaryData, tinyxml2::XMLElement &Eletype);

    // 针对二进制数据的反序列化
    void readfromXML(std::vector<uint8_t> &binaryData, tinyxml2::XMLElement &Eletype);
}