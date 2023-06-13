#include <iostream>
#include <vector>

class Solution
{
public:
    int numTimesAllBlue(std::vector<int> &flips)
    {
        int ans = 0, n = flips.size(), max = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (flips[i - 1] > max)
            {
                max = flips[i - 1];
            }
            if (i == max)
            {
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}