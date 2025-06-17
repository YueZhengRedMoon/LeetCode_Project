#include <iostream>

class Solution
{
public:
    int maxDiff(int num)
    {
        std::string numStr = std::to_string(num);
        std::string maxA = numStr, minB = numStr;

        int n = numStr.size(), i;
        char x = 'x';
        for (i = 0; i < n; ++i)
        {
            if (maxA[i] != '9')
            {
                x = maxA[i];
                break;
            }
        }
        for (; i < n; ++i)
        {
            if (maxA[i] == x)
            {
                maxA[i] = '9';
            }
        }

        if (minB[0] != '1')
        {
            x = minB[0];
            for (i = 0; i < n; ++i)
            {
                if (minB[i] == x)
                {
                    minB[i] = '1';
                }
            }
        }
        else    // minB[0] == '1'
        {
            for (i = 1; i < n; ++i)
            {
                if (minB[i] > '1')
                {
                    x = minB[i];
                    break;
                }
            }
            for (; i < n; ++i)
            {
                if (minB[i] == x)
                {
                    minB[i] = '0';
                }
            }
        }

        return std::stoi(maxA) - std::stoi(minB);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
