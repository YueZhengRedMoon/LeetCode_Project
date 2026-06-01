#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumCost(std::vector<int>& cost)
    {
        std::sort(cost.begin(), cost.end(), std::greater<>());
        int ans = 0, i = 0, n = cost.size();
        while (i < n)
        {
            ans += cost[i++];
            if (i < n)
            {
                ans += cost[i];
                i += 2;
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