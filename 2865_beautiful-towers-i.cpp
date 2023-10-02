#include <iostream>
#include <vector>

class Solution
{
public:
    long long maximumSumOfHeights(std::vector<int> &maxHeights)
    {
        long long ans = 0;
        int n = maxHeights.size();
        for (int i = 0; i < n; ++i)
        {
            long long sum = maxHeights[i];
            int lastHeight = maxHeights[i];
            for (int j = i - 1; j >= 0; --j)
            {
                int curHeight = std::min(maxHeights[j], lastHeight);
                sum += curHeight;
                lastHeight = curHeight;
            }
            lastHeight = maxHeights[i];
            for (int k = i + 1; k < n; ++k)
            {
                int curHeight = std::min(maxHeights[k], lastHeight);
                sum += curHeight;
                lastHeight = curHeight;
            }
            if (sum > ans)
                ans = sum;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
