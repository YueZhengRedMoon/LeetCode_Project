#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfArrays(std::vector<int>& differences, int lower, int upper)
    {
        long long x = 0, maxX = 0, minX = 0;
        int n = differences.size();
        for (int i = 0; i < n; ++i)
        {
            x += differences[i];
            if (x > maxX)
                maxX = x;
            if (x < minX)
                minX = x;
        }

        // 令minX = lower，则 maxX = maxX + lower - minX
        maxX += lower - minX;

        return std::max(0ll, upper - maxX + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
