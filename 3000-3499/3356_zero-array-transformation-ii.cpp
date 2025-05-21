#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        int n = nums.size(), q = queries.size();

        std::vector<int> diff(n + 1);

        // 检查处理前k个查询后，是否可以将nums变成零数组
        auto check = [&](int k) -> bool {
            std::fill(diff.begin(), diff.end(), 0);
            for (int i = 0; i < k; ++i)
            {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] += val;
                diff[r + 1] -= val;
            }

            for (int i = 0, sumD = 0; i < n; ++i)
            {
                sumD += diff[i];
                if (sumD < nums[i])
                    return false;
            }
            return true;
        };

        int l = 0, r = q + 1, ans = -1;
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (check(mid)) // 通过mid次操作，可以将nums变为零数组
            {
                ans = mid;
                r = mid;
            }
            else    // 通过mid次操作，不能将nums变为零数组
            {
                l = mid + 1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
