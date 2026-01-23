#include <iostream>
#include <vector>
#include <set>

class Solution
{
public:
    int minimumPairRemoval(std::vector<int>& nums)
    {
        int n = nums.size();
        std::set<std::pair<long long, int>> pairs;  // (相邻元素和，左边那个数的下标)
        int dec = 0;    // 在相邻元素中，满足「左边元素>右边元素」的个数
        for (int i = 0; i + 1 < n; ++i)
        {
            int x = nums[i], y = nums[i + 1];
            if (x > y)
            {
                ++dec;
            }
            pairs.emplace(x + y, i);
        }

        std::set<int> idx;  // 剩余下标
        for (int i = 0; i < n; ++i)
        {
            idx.insert(i);
        }

        std::vector<long long> a(nums.begin(), nums.end());
        int ans = 0;
        while (dec > 0)
        {
            ++ans;

            // 删除相邻元素和最小的一对
            auto [s, i] = *pairs.begin();
            pairs.erase(pairs.begin());

            auto it = idx.lower_bound(i);

            // (当前元素，下一个数)
            auto nxtIt = std::next(it);
            int nxt = *nxtIt;
            if (a[i] > a[nxt])  // (a[i],a[nxt])是递减对，即将删除a[i]，递减对数量减少
            {
                --dec;
            }

            // (前一个数，当前元素)
            if (it != idx.begin())
            {
                int pre = *std::prev(it);
                if (a[pre] > a[i])  // (a[pre],a[i])是递减对，即将删除a[i]，递减对数量减少
                {
                    --dec;
                }
                if (a[pre] > s) // s将添加到a[pre]后，(a[pre],s)是递减对，递减对数量增加
                {
                    ++dec;
                }
                pairs.erase({a[pre] + a[i], pre});
                pairs.emplace(a[pre] + s, pre);
            }

            // (下一个数，下下一个数)
            auto nxt2It = std::next(nxtIt);
            if (nxt2It != idx.end())
            {
                int nxt2 = *nxt2It;
                if (a[nxt] > a[nxt2])   // (a[nxt],a[nxt2])是递减对，即将删除a[nxt]，递减对数量减少
                {
                    --dec;
                }
                if (s > a[nxt2])    // s将添加到a[nxt2]前，(s,a[nxt2])是递减对，递减对数量增加
                {
                    ++dec;
                }
                pairs.erase({a[nxt] + a[nxt2], nxt});
                pairs.emplace(s + a[nxt2], i);
            }

            a[i] = s;   // 把a[nxt]加到a[i]中
            idx.erase(nxt); // 删除nxt
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}