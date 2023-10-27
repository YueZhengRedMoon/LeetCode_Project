#include <iostream>
#include <vector>

class Codec
{
public:

    // Encodes a list of strings to a single string.
    std::string encode(std::vector<std::string> &strs)
    {
        std::string res;
        for (const std::string &str : strs)
        {
            res += getLen(str) + str;
        }
        return res;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(std::string s)
    {
        std::vector<std::string> res;
        int i = 0, sLen = s.size();
        while (i < sLen)
        {
            unsigned int len = 0;
            for (int j = 0; j < 4; ++j)
            {
                len = (len << 8) + s[i + j] & 0xFF;
            }
            i += 4;
            res.push_back(s.substr(i, len));
            i += len;
        }
        return res;
    }

private:
    /** 获取str的长度，将其编码为4个字符 */
    std::string getLen(const std::string &str)
    {
        std::string res(4, 0);
        unsigned int len = str.size();
        for (int i = 3; i >= 0; --i)
        {
            res[3 - i] = static_cast<char>((len >> i * 8) & 0xFF);
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}