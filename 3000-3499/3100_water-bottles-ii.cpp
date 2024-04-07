#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    // n:numBottles, m:numExchange
    int maxBottlesDrunk(int n, int m)
    {
        // 设可以通过换空瓶子换x瓶水，换的空瓶数为(m + m+1 + m+2 + ... + m+x-1)，喝的水的数量应该大于空瓶的数量
        // n+x > (m + m + x) * (x - 1) / 2
        int t = 2 * m - 3;
        return n + (int) std::ceil((std::sqrt(t * t + 8 * n) - t) / 2) - 1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
