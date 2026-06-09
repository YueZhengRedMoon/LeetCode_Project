#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

// 获取表示n所需的二进制位数
int bitWidth(int n)
{
    return 32 - __builtin_clz(n);
}

class SparseTable
{
public:
    // 预处理，时间复杂度O(n * log n)
    SparseTable(const std::vector<int>& nums)
    : stMin(bitWidth(nums.size()), std::vector<int>(nums.size()))
    , stMax(bitWidth(nums.size()), std::vector<int>(nums.size()))
    {
        int n = nums.size();
        int w = bitWidth(n);

        // 初始化，起始位置为j，区间长度为2^0的区间，即[j,j+1)的最小/大值即为nums[j]
        for (int j = 0; j < n; ++j)
        {
            stMin[0][j] = nums[j];
            stMax[0][j] = nums[j];
        }

        for (int i = 1; i < w; ++i)
        {
            for (int j = 0; j <= n - (1 << i); ++j)
            {
                // 区间[j,j+2^i)的最小/大值 = 区间[j,j+2^(i-1)) ∪ 区间[j+2^(i-1),j+2^(i-1)+2^(i-1))的最小/大值
                stMin[i][j] = std::min(stMin[i - 1][j], stMin[i - 1][j + (1 << (i - 1))]);
                stMax[i][j] = std::max(stMax[i - 1][j], stMax[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    // k = floor(log2(r - l))
    // 用区间[l, l+2^k)和[r-2^k,r)来计算区间的最小/大值，这2个区间可能重叠
    // 右区间要用[r-2^k,r)而非[l+2^k, l+2^k+2^k)，因为l+2^k+2^k可能>r
    // 例如求区间[0, 5)的最大/小值，bitWidth(5)=3，k=2，因此用区间[0,4)和区间[1,5)来计算

    // 查询区间[l, r)的最小值
    int queryMin(int l, int r) const
    {
        int k = bitWidth(r - l) - 1;
        return std::min(stMin[k][l], stMin[k][r - (1 << k)]);
    }

    // 查询区间[l, r)的最大值
    int queryMax(int l, int r) const
    {
        int k = bitWidth(r - l) - 1;
        return std::max(stMax[k][l], stMax[k][r - (1 << k)]);
    }

    // 计算区间[l, r)的最大值-最小值
    int query(int l, int r) const
    {
        int k = bitWidth(r - l) - 1;
        return std::max(stMax[k][l], stMax[k][r - (1 << k)]) - std::min(stMin[k][l], stMin[k][r - (1 << k)]);
    }

private:
    std::vector<std::vector<int>> stMin;    // stMin[i][j]:区间[j,j+2^i)的最小值
    std::vector<std::vector<int>> stMax;    // stMax[i][j]:区间[j,j+2^i)的最大值
};

class Solution
{
public:
    long long maxTotalValue(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        SparseTable st(nums);

        std::priority_queue<std::tuple<int, int, int>> pq;
        for (int i = 0; i < n; ++i)
        {
            pq.emplace(st.query(i, n), i, n);   // 子数组值，左端点，右端点加一
        }

        long long ans = 0;
        while (k-- && std::get<0>(pq.top()))
        {
            auto [d, l, r] = pq.top();
            pq.pop();
            ans += d;
            // std::cout << "d = " << d << ", l = " << l << ", r = " << r << ", ans = " << ans << std::endl;
            pq.emplace(st.query(l, r - 1), l, r - 1);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {29,44,3,20};
    int k = 4;
    long long ans = solution.maxTotalValue(nums, k);
    std::cout << ans << std::endl;
    return 0;
}