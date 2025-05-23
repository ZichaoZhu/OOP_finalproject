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
#include "tinyxml2.h"

namespace xml
{
    /**
     * @brief Write the is-arithmetic type to XML.
     * @tparam Write as this format: <val = "...">
     */
    template<typename T>
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
    template<typename T>
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
    template<typename T>
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
    template<typename T>
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