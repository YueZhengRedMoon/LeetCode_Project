#include <iostream>
#include <vector>

class Solution
{
public:
    std::string removeTrailingZeros(std::string num)
    {
        int pos = num.find_last_not_of('0');
        if (pos != std::string::npos)
        {
            num.resize(pos + 1);
        }
        return num;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}