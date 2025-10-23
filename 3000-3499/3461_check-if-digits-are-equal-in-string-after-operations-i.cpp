#include <iostream>
#include <vector>

class Solution
{
public:
    bool hasSameDigits(std::string s)
    {
        int sLen = s.size();
        while (sLen > 2)
        {
            std::string newS;
            newS.reserve(sLen - 1);
            for (int i = 0; i < sLen - 1; ++i)
            {
                newS.push_back(((s[i] - '0') + (s[i + 1] - '0')) % 10 + '0');
            }
            --sLen;
            std::swap(s, newS);
        }
        return s[0] == s[1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}