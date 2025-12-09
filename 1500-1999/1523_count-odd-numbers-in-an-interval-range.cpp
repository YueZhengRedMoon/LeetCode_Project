#include <iostream>
#include <vector>

class Solution
{
public:
    int countOdds(int low, int high)
    {
        return countOdds(high) - countOdds(low - 1);
    }

private:
    // 返回[0, n]之间的奇数数目
    int countOdds(int n)
    {
        if (n <= 0)
            return 0;

        return n % 2 ? n / 2 + 1 : n / 2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}