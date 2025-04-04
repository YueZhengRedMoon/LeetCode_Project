#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> minCosts(std::vector<int>& cost)
    {
        int n = cost.size();
        for (int i = 1; i < n; ++i)
        {
            if (cost[i - 1] < cost[i])
                cost[i] = cost[i - 1];
        }
        return cost;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
