#include <iostream>
#include <vector>

template<typename T>
class FenwickTree
{
public:
    // 使用下标1到n
    FenwickTree(int n) : tree(n + 1) {}

    // a[i]增加val, 1 <= i <= n
    void update(int i, T val)
    {
        for (; i < tree.size(); i += i & -i)
        {
            tree[i] += val;
        }
    }

    // 求前缀和a[1] + ... + a[i], 1 <= i <= n
    T pre(int i) const
    {
        T res = 0;
        for (; i > 0; i &= i - 1)
        {
            res += tree[i];
        }
        return res;
    }

private:
    std::vector<T> tree;
};

class Solution
{
public:
    long long goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int n = nums1.size();
        std::vector<int> p(n);
        for (int i = 0; i < n; ++i)
        {
            p[nums1[i]] = i;
        }

        long long ans = 0;
        FenwickTree<int> t(n);
        for (int i = 0; i < n - 1; ++i) // 枚举三元组中间的值
        {
            int y = p[nums2[i]];
            int less = t.pre(y);
            ans += (long long) less * (n - 1 - y - (i - less));
            t.update(y + 1, 1);
        }
        return ans;
    }
};

// 不用树状数组，暴力求less
class Solution2
{
public:
    long long goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int n = nums1.size();

        // 置换
        // 将nums1转换为[0, 1, 2, ..., n-1]的排列A，得到映射关系p
        std::vector<int> p(n);
        for (int i = 0; i < n; ++i)
        {
            p[nums1[i]] = i;
        }

        // 将映射关系p应用到nums2上，得到排列B
        std::vector<int> b(n);
        for (int i = 0; i < n; ++i)
        {
            b[i] = p[nums2[i]];
        }

        // 求排列B中有多少个严格递增且长度为3的子序列
        long long ans = 0;
        for (int j = 1; j < n - 1; ++j) // 枚举三元组中间的数
        {
            int less = 0;
            for (int i = 0; i < j; ++i)
                less += b[i] < b[j];

            // 对于当前枚举的数y=b[j]
            // 整个排列B中比y大的数有n-1-y个
            // y左侧比y大的数有j-less个
            // 则y右侧比y大的数有n-1-y-(j -less)个
            ans += (long long) less * (n - 1 - b[j] - (j - less));
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> nums1 = {4, 0, 1, 3, 2}, nums2 = {4, 1, 0, 2, 3};
    long long ans = solution.goodTriplets(nums1, nums2);
    std::cout << ans << std::endl;
    return 0;
}
