#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    std::vector<long long> handleQuery(std::vector<int> &nums1, std::vector<int> &nums2,
                                       std::vector<std::vector<int>> &queries)
    {
        int n = nums1.size();
        cnt1.resize(4 * n, 0);
        flipped.resize(4 * n, false);

        // 初始化线段树
        build(nums1, 1, 1, n);

        // 查询
        long long sum = std::accumulate(nums2.begin(), nums2.end(), 0ll);
        std::vector<long long> ans;
        for (const std::vector<int> &query : queries)
        {
            if (query[0] == 1)
                update(1, 1, n, query[1] + 1, query[2] + 1);
            else if (query[0] == 2)
                sum += static_cast<long long>(query[1]) * cnt1[1];
            else
                ans.push_back(sum);
        }

        return ans;
    }

private:
    std::vector<int> cnt1;  // 线段树每个节点所代表的区间中1的个数
    std::vector<bool> flipped;

    /** 初始化线段树，计算每个节点所表示的区间中1的个数
     * @param nums:用来初始化线段树的数组
     * @param O:线段树节点编号
     * @param l:节点所表示区间的左端点
     * @param r:节点所表示区间的右端点
     * */
    void build(const std::vector<int> &nums, int o, int l, int r)
    {
        if (l == r)
        {
            cnt1[o] = nums[l - 1];  // 区间的端点是从1开始的
            return;
        }
        int m = (l + r) >> 1;
        build(nums, o * 2, l, m);
        build(nums, o * 2 + 1, m + 1, r);
        maintain(o);
    }

    /** 维护区间中1的个数 */
    void maintain(int o)
    {
        cnt1[o] = cnt1[o * 2] + cnt1[o * 2 + 1];
    }

    /** 更新区间[L, R]
     * @param O:线段树节点编号
     * @param l:节点所表示区间的左端点
     * @param r:节点所表示区间的右端点
     * @param L:要更新区间的左端点
     * @param R:要更新区间的右端点
     * */
    void update(int o, int l, int r, int L, int R)
    {
        // 当前节点所表示的区间已经被更新区间包含，不用再继续递归
        if (L <= l && r <= R)
        {
            flip(o, l, r);
            return;
        }
        int m = (l + r) >> 1;
        // 该区间在此前被翻转过，将翻转向下传递
        if (flipped[o])
        {
            flip(o * 2, l, m);
            flip(o * 2 + 1, m + 1, r);
            flipped[o] = false;
        }
        if (m >= L)
            update(o * 2, l, m, L, R);
        if (m < R)  // m + 1 <= R
            update(o * 2 + 1, m + 1, r, L, R);
        maintain(o);
    }

    /** 翻转节点所表示的区间
     * @param O:线段树节点编号
     * @param l:节点所表示区间的左端点
     * @param r:节点所表示区间的右端点
     * */
    void flip(int o, int l, int r)
    {
        cnt1[o] = r - l + 1 - cnt1[o];
        flipped[o] = !flipped[o];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}