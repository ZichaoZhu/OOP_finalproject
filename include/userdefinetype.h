#pragma once
#include <string>
#include <vector>

namespace userdefinetype
{
    struct UserDefinedType
    {
        int idx;
        std::string name;
        std::vector<double> data;
    };
    void set(UserDefinedType &t, int idx, std::string name, std::vector<double> data)
    {
        t.idx = idx;
        t.name = name;
        t.data = data;
    }
}