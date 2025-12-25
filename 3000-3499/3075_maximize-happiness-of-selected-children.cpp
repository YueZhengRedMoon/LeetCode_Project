#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long maximumHappinessSum(std::vector<int>& happiness, int k)
    {
        std::sort(happiness.begin(), happiness.end(), std::greater<>());
        long long ans = 0;
        for (int i = 0; i < std::min<int>(happiness.size(), k); ++i)
        {
            if (happiness[i] - i <= 0)
                break;
            ans += happiness[i] - i;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}