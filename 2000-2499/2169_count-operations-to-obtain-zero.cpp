#include <iostream>
#include <vector>

class Solution
{
public:
    int countOperations(int num1, int num2)
    {
        int ans = 0;
        while (num1 > 0 && num2 > 0)
        {
            if (num1 >= num2)
                num1 -= num2;
            else
                num2 -= num1;
            ++ans;
        }
        return ans;
    }
};

class Solution2
{
public:
    int countOperations(int x, int y)
    {
        int ans = 0;
        while (y > 0)
        {
            ans += x / y;
            x %= y;
            std::swap(x, y);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}