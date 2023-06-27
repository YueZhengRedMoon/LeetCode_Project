#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minimumIncompatibility(std::vector<int> &nums, int k)
    {
        int count[17]{0};
        int maxCount = 0;
        for (int num : nums)
        {
            if (++count[num] > maxCount)
            {
                maxCount = count[num];
            }
        }
        if (maxCount > k)
            return -1;

        int n = nums.size();
        int m = n / k;    // 每个子集的大小
        // 遍历所有长度为n且恰好有m个1的二进制数
        int begin = (1 << m) - 1;   // 0000111
        int end = begin << (n - m); // 1110000
        int x = begin;
        while (x <= end)
        {
            int res = calcIncompatibility(x, nums);
            if (res != inf)
            {
                subsets.emplace_back(x, res);
            }

            int lb = x & -x;
            int left = x + lb;
            int right = (x ^ (left)) / lb >> 2;
            x = left | right;
        }

        backtracking(0, 0, 0);
        return memo[(1 << n) - 1];
    }

private:
    std::unordered_map<int, int> memo;
    std::vector<std::pair<int, int>> subsets;
    const int inf{0x3f3f3f3f};

    int calcIncompatibility(int bitset, std::vector<int> &nums)
    {
        int max = -inf;
        int min = inf;
        bool visited[17]{false};
        int i = 0;
        while (bitset > 0)
        {
            if (bitset & 1)
            {
                if (visited[nums[i]])   // 出现了重复元素，集合是不合法的
                {
                    return inf;
                }
                else
                {
                    visited[nums[i]] = true;
                    if (nums[i] > max)
                        max = nums[i];
                    if (nums[i] < min)
                        min = nums[i];
                }
            }
            ++i;
            bitset >>= 1;
        }
        return max - min;
    }

    void backtracking(int s, int begin, int incomp)
    {
        auto it = memo.find(s);
        if (it != memo.end() && it->second <= incomp)
            return;

        memo[s] = incomp;
        for (int i = begin; i < subsets.size(); ++i)
        {
            if ((s & subsets[i].first) == 0)
            {
                backtracking(s | subsets[i].first, i + 1, incomp + subsets[i].second);
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}