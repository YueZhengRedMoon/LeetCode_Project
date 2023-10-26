#include <iostream>
#include <vector>

class Solution
{
public:
    int countDigits(int num)
    {
        int ans = 0, n = num;
        while (n)
        {
            if (num % (n % 10) == 0)
                ++ans;
            n /= 10;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}