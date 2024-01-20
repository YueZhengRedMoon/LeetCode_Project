#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    /**
     * 1.每个下标至多操作1次，因为对下标i操作多次的话，可以只保留最后一次，
     * 前面对下标i的操作是多余的（反而会让其他数字变的更大）。
     *
     * 2.尝试枚举答案：第t秒的元素之和最小是多少？
     *  - 设nums1的元素和为s1, nums2的元素和为s2；
     *  - 如果不进行任何操作，第t秒的元素和为：s1 + s2 * t；
     *  - 如何在t秒中进行操作，使得t秒时减去的元素和最大，这样剩下的元素和就是最小的；
     *  - 于是问题转换为第t秒减去的元素和最大是多少？
     *
     *  3.下标为i的元素在第t秒的值
     *   - 对于下标为i的元素，假设不对其进行操作，则其第t秒的值为：nums1[i] + t * nums2[i];
     *   - 如果在第k秒时对其进行操作，则其第t秒的值为：nums2 * (t - k)；
     *   - 则下标为i的元素在第t秒时减少的和为：nums1[i] + t * nums2[i] - nums2 * (t - k) = nums1[i] + nums2[i] * k，
     *     其中k为对下标为i的元素操作的时间；
     * */

    int minimumTime(std::vector<int> &nums1, std::vector<int> &nums2, int x)
    {
        int n = nums1.size();
        int s1 = std::accumulate(nums1.begin(), nums1.end(), 0);
        int s2 = std::accumulate(nums2.begin(), nums2.end(), 0);

        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {return nums2[a] < nums2[b];});

        // dp[i + 1][j]:在[0:i+1]中选择j个元素操作，能减去的最大和
        std::vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j > 0; --j)
            {
                dp[j] = std::max(dp[j], dp[j - 1] + nums1[idx[i]] + j * nums2[idx[i]]);
            }
        }

        for (int t = 0; t <= n; ++t)
        {
            if (s1 + s2 * t - dp[t] <= x)
                return t;
        }

        return -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
