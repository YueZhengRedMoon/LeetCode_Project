#include <iostream>
#include <vector>
#include <unordered_map>
#include <forward_list>

/** 超内存 */
class Solution
{
public:
    int longestEqualSubarray(std::vector<int> &nums, int k)
    {
        int n = nums.size(), ans = 1;
        std::unordered_map<int, int> numLastIndex;
        std::vector<std::vector<std::pair<int, int>>> dp(n);

        for (int i = 0; i < n; ++i)
        {
            auto mapIt = numLastIndex.find(nums[i]);
            // nums[i]是第一次出现
            if (mapIt == numLastIndex.end())
            {
                numLastIndex[nums[i]] = i;
                dp[i].emplace_back(1, 0);
            }
            // nums[i]此前出现过
            else
            {
                int lastIndex = mapIt->second;
                mapIt->second = i;
                int dis = i - lastIndex - 1;    // 当前nums[i]与上一个nums[i]之间有多少个元素
                bool hasZeroDel = false;
                for (auto [len, del] : dp[lastIndex])
                {
                    if (del == 0 && dis == 0)
                        hasZeroDel = true;
                    if (del + dis <= k)
                    {
                        ++len;
                        dp[i].emplace_back(len, del + dis);
                        if (len > ans)
                        {
                            ans = len;
                        }
                    }
                }
                if (!hasZeroDel)
                {
                    dp[i].emplace_back(1, 0);
                }
            }
        }
        return ans;
    }
};

/** 超时 */
class Solution2
{
public:
    int longestEqualSubarray(std::vector<int> &nums, int k)
    {
        int n = nums.size(), ans = 1;
        std::unordered_map<int, std::forward_list<std::pair<int, int>>> dp;
        std::unordered_map<int, int> numLastIndex;

        for (int i = 0; i < n; ++i)
        {
            auto mapIt = dp.find(nums[i]);
            if (mapIt == dp.end())
            {
                dp[nums[i]].emplace_front(1, 0);
                numLastIndex[nums[i]] = i;
            }
            else
            {
                std::forward_list<std::pair<int, int>> &items = mapIt->second;
                std::forward_list<std::pair<int, int>> newItems;
                int &lastIndex = numLastIndex[nums[i]];
                bool hasZeroDel = false;
                for (auto [len, del] : items)
                {
                    int newLen = len + 1, newDel = del + i - lastIndex - 1;
                    if (newDel <= k)
                    {
                        newItems.emplace_front(newLen, newDel);
                        if (newLen > ans)
                            ans = newLen;
                        if (newDel == 0)
                            hasZeroDel = true;
                    }
                }
                if (!hasZeroDel)
                    newItems.emplace_front(1, 0);
                std::swap(items, newItems);
                lastIndex = i;
            }
        }

        return ans;
    }
};

class Solution3
{
public:
    int longestEqualSubarray(std::vector<int> &nums, int k)
    {
        int n = nums.size(), ans = 0;
        std::vector<std::vector<int>> pos(n + 1);
        for (int i = 0; i < n; ++i)
            pos[nums[i]].push_back(i - pos[nums[i]].size());
        for (auto &ps : pos)
        {
            int left = 0;
            for (int right = 0; right < ps.size(); ++right)
            {
                while (ps[right] - ps[left] > k)    // 要删除的数太多了
                    ++left;
                ans = std::max(ans, right - left + 1);
            }
        }
        return ans;
    }
};

class Solution4
{
public:
    int longestEqualSubarray(std::vector<int> &nums, int k)
    {
        int n = nums.size(), ans = 0;
        std::unordered_map<int, std::vector<int>> positions;
        for (int i = 0; i < n; ++i)
        {
            positions[nums[i]].push_back(i);
        }
        for (const auto &item : positions)
        {
            const std::vector<int> &pos = item.second;
            int left = 0;
            for (int right = 0; right < pos.size(); ++right)
            {
                while (pos[right] - pos[left] + - (right - left) > k)
                    ++left;
                ans = std::max(ans, right - left + 1);
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
