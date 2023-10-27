#include <iostream>

class Solution
{
public:
    int balancedStringSplit(std::string s)
    {
        int numL = 0, numR = 0;
        int result = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == 'R')
            {
                ++numR;
            }
            else
            {
                ++numL;
            }
            if (numR == numL)
            {
                ++result;
                numR = 0;
                numL = 0;
            }
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
