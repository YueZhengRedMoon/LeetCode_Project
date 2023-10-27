#include <iostream>
#include <vector>

class Solution
{
public:
    int countTime(std::string time)
    {
        int result = 1;
        if (time[0] == '?')
        {
            if ((time[1] >= '4' && time[1] <= '9'))
            {
                result = 2;
            }
            else
            {
                result = 3;
            }
        }
        if (time[1] == '?')
        {
            if (time[0] == '?')
            {
                result = 24;
            }
            else if (time[0] == '2')
            {
                result = 4;
            }
            else
            {
                result = 10;
            }
        }
        if (time[3] == '?')
        {
            result *= 6;
        }
        if (time[4] == '?')
        {
            result *= 10;
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}