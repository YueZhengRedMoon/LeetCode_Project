#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> solveQueries(std::vector<int>& nums, std::vector<int>& queries)
    {
        int n = nums.size();
        std::unordered_map<int, std::vector<int>> pos;
        for (int i = 0; i < n; ++i)
        {
            pos[nums[i]].push_back(i);
        }

        for (int& q : queries)
        {
            int x = nums[q];    // 要查询的元素
            std::vector<int>& posX = pos[x];
            int m = posX.size();
            if (m == 1)
            {
                q = -1;
                continue;
            }
            int j = std::lower_bound(posX.begin(), posX.end(), q) - posX.begin();
            int i = (j - 1 + m) % m, k = (j + 1) % m;

            int dij = std::abs(posX[i] - posX[j]), djk = std::abs(posX[j] - posX[k]);
            q = std::min({dij, n - dij, djk, n - djk});
        }
        return queries;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}