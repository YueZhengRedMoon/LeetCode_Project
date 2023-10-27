#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    int splitNum(int num)
    {
        std::string numStr = std::to_string(num);
        std::string num1Str, num2Str;
        std::sort(numStr.begin(), numStr.end());
        int len = numStr.size();
        for (int i = 0; i < len; ++i)
        {
            num1Str.push_back(numStr[i++]);
            if (i < len)
                num2Str.push_back(numStr[i]);
        }
        return std::stoi(num1Str) + std::stoi(num2Str);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
