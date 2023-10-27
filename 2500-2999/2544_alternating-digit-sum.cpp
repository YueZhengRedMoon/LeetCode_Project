#include <iostream>
#include <vector>

class Solution
{
public:
    int alternateDigitSum(int n)
    {
        std::string s = std::to_string(n);
        int sign = 1, sum = 0;
        for (char c : s)
        {
            sum += sign * (c - '0');
            sign *= -1;
        }
        return sum;
    }
};

class Solution2
{
public:
    int alternateDigitSum(int n)
    {
        int sign = 1, sum = 0;
        while (n > 0)
        {
            sum += sign * (n % 10);
            n /= 10;
            sign *= -1;
        }
        if (sign == 1)
        {
            sum = -sum;
        }
        return sum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
