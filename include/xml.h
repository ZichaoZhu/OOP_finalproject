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
#include "tinyxml2.h"
#include <iostream>

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
                t = static_cast<T>(std::atof(val));
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
}