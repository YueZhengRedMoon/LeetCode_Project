#include <iostream>

class Solution
{
public:
    bool checkPowersOfThree(int n)
    {
        while (n)
        {
            if (n % 3 == 2)
                return false;
            n /= 3;
        }
        return true;
    }
};

int main()
{
    const int MAX_N = 1'000'000;
    int x = 1;
    while (x <= MAX_N)
    {
        std::cout << x << " ";
        x *= 3;
    }
    return 0;
}
