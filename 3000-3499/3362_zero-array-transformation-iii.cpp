#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Solution
{
public:
    int maxRemoval(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        std::sort(queries.begin(), queries.end());
        int n = nums.size(), j = 0, sumD = 0;
        std::vector<int> diff(n + 1, 0);
        std::priority_queue<int> pq;    // 大顶堆
        for (int i = 0; i < n; ++i)
        {
            sumD += diff[i];

            // 维护左端点<=i的区间
            while (j < queries.size() && queries[j][0] <= i)
            {
                pq.push(queries[j][1]);
                ++j;
            }

            // 选择右端点最大的区间
            while (sumD < nums[i] && !pq.empty() && pq.top() >= i)
            {
                ++sumD;
                --diff[pq.top() + 1];
                pq.pop();
            }

            if (sumD < nums[i])
                return -1;
        }
        return pq.size();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
