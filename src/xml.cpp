#include <string>
#include <vector>
#include <cstring>
#include "xml.h"

namespace xml
{
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string base64Encode(const std::vector<uint8_t> &data)
    {
        std::string encoded;
        int val = 0, valb = -6;
        for (uint8_t c : data)
        {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0)
            {
                encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
            encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (encoded.size() % 4)
            encoded.push_back('=');
        return encoded;
    }

    std::vector<uint8_t> base64Decode(const std::string &encoded)
    {
        std::vector<uint8_t> decoded;
        std::vector<int> T(256, -1);
        for (int i = 0; i < 64; i++)
            T[base64_chars[i]] = i;
        int val = 0, valb = -8;
        for (uint8_t c : encoded)
        {
            if (T[c] == -1)
                break;
            val = (val << 6) + T[c];
            valb += 6;
            if (valb >= 0)
            {
                decoded.push_back((val >> valb) & 0xFF);
                valb -= 8;
            }
        }
        return decoded;
    }

    void writeintoXML(const std::vector<uint8_t> &binaryData, tinyxml2::XMLElement &Eletype)
    {
        std::string encoded = base64Encode(binaryData);
        writeintoXML(encoded, Eletype);
    }

    void readfromXML(std::vector<uint8_t> &binaryData, tinyxml2::XMLElement &Eletype)
    {
        std::string encoded;
        readfromXML(encoded, Eletype);
        binaryData = base64Decode(encoded);
    }
}