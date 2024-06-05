#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Fenwick
{
public:
    Fenwick(int n) : tree(n) {}

    // 把下标为i的元素加1
    void add(int i)
    {
        while (i < tree.size())
        {
            ++tree[i];
            i += i & -i;
        }
    }

    // 返回下标在[1, i]的元素之和
    int pre(int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += tree[i];
            i &= i - 1; // i = i - (i & -i)，将i最低位的1变为0
        }
        return res;
    }

private:
    std::vector<int> tree;
};

class Solution
{
public:
    std::vector<int> resultArray(std::vector<int>& nums)
    {
        // 获取nums排序且去重后的副本
        std::vector<int> sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        std::unordered_map<int, int> idx;
        for (int i = 0; i < m; ++i)
        {
            idx[sorted[i]] = i + 1;
        }

        std::vector<int> arr1({nums[0]}), arr2({nums[1]});
        arr1.reserve(nums.size());
        Fenwick t1(m + 1), t2(m + 1);
        t1.add(idx[nums[0]]);
        t2.add(idx[nums[1]]);
        for (int i = 2; i < nums.size(); ++i)
        {
            int v = idx[nums[i]] + 1;
            int gc1 = arr1.size() - t1.pre(v), gc2 = arr2.size() - t2.pre(v);
            if (gc1 > gc2 || (gc1 == gc2 && arr1.size() <= arr2.size()))
            {
                arr1.push_back(nums[i]);
                t1.add(v);
            }
            else
            {
                arr2.push_back(nums[i]);
                t2.add(v);
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());

        return arr1;
    }
};

class BinaryIndexedTree
{
public:
    BinaryIndexedTree(int n) : tree(n + 1) {}

    // 将下标为i的元素增加delta
    void add(int i, int delta)
    {
        while (i < tree.size())
        {
            tree[i] += delta;
            i += i & -i;
        }
    }

    // 求区间[1, i]的前缀和
    int pre(int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += tree[i];
            i &= i - 1;
        }
        return res;
    }

private:
    std::vector<int> tree;  // 树状数组，下标从1开始
};

class Solution2
{
public:
    std::vector<int> resultArray(std::vector<int>& nums)
    {
        // 获取nums排序且去重后的副本
        std::vector<int> sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
        int m = sorted.size();

        std::unordered_map<int, int> idx;
        for (int i = 0; i < m; ++i)
        {
            idx[sorted[i]] = m - i;
        }

        std::vector<int> arr1({nums[0]}), arr2({nums[1]});
        arr1.reserve(nums.size());
        BinaryIndexedTree bit(m);
        bit.add(idx[nums[0]], 1);
        bit.add(idx[nums[1]], -1);
        for (int i = 2; i < nums.size(); ++i)
        {
            int index = idx[nums[i]];
            int d = bit.pre(index - 1);
            if (d > 0 || (d == 0 && arr1.size() <= arr2.size()))
            {
                arr1.push_back(nums[i]);
                bit.add(index, 1);
            }
            else
            {
                arr2.push_back(nums[i]);
                bit.add(index, -1);
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());

        return arr1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
