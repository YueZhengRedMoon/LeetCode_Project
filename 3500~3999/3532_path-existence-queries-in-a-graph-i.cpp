#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<bool> pathExistenceQueries(int n, std::vector<int>& nums, int maxDiff, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> component(n, 0);
        for (int i = 1; i < n; ++i)
        {
            component[i] = component[i - 1] + (nums[i] - nums[i - 1] > maxDiff);
        }
        int m = queries.size();
        std::vector<bool> ans(m);
        for (int i = 0; i < m; ++i)
        {
            int u = queries[i][0], v = queries[i][1];
            ans[i] = component[u] == component[v];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}