#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());  // 把nums转换成哈希集合
        int ans = 0;
        for (int x : set)   // 遍历哈希集合
        {
            if (set.find(x - 1) != set.end())   // 如果 x 不是序列的起点，直接跳过
            {
                continue;
            }

            // x 是序列的起点
            int y = x + 1;
            while (set.find(y) != set.end())    // 不断查找下一个数是否在哈希集合中
            {
                ++y;
            }
            // 循环结束后，y-1 是最后一个在哈希集合中的数
            ans = std::max(ans, y - x); // 从 x 到 y-1 一共 y-x 个数

            // 设 m 为 nums 中的不同元素个数（即哈希集合的大小）,各个连续序列（链）是互相独立的
            // 如果我们发现其中一条链的长度至少为m/2，则不可能还有一条长度>m/2的链，答案不再会增大
            if (ans * 2 >= set.size())
            {
                break;
            }
        }
        return ans;
    }
};

class MySolution
{
public:
    int longestConsecutive(std::vector<int> &nums)
    {
        for (int num : nums)
        {
            if (parent.find(num) == parent.end())
            {
                parent[num] = num;
                if (parent.find(num + 1) != parent.end())
                {
                    unite(num, num + 1);
                }

                if (parent.find(num - 1) != parent.end())
                {
                    unite(num - 1, num);
                }
            }
        }

        int ans = 0;
        std::unordered_map<int, int> setSize;
        for (auto it = parent.begin(); it != parent.end(); ++it)
        {
            int x = find(it->first);
            ans = std::max(ans, ++setSize[x]);
        }

        return ans;
    }

private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return;
        }
        int &rankX = rank[x];
        int &rankY = rank[y];
        if (rankX < rankY)
        {
            parent[x] = y;
        }
        else
        {
            parent[y] = x;
            if (rankX == rankY)
            {
                ++rankX;
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
