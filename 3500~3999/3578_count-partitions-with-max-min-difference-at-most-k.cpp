#include <iostream>
#include <vector>
#include <set>
#include <queue>

class Solution
{
public:
    int countPartitions(std::vector<int>& nums, int k)
    {
        const int MOD = 1'000'000'007;
        int n = nums.size();
        std::deque<int> minQ, maxQ; // minQ:单调减队列, maxQ:单调增队列
        std::vector<int> f(n + 1);
        f[0] = 1;
        long long sumF = 0; // 窗口中的f[i]之和
        int left = 0;

        for (int i = 0; i < n; ++i)
        {
            int x = nums[i];

            // 1.入
            sumF += f[i];

            while (!minQ.empty() && x <= nums[minQ.back()])
            {
                minQ.pop_back();
            }
            minQ.push_back(i);

            while (!maxQ.empty() && x >= nums[maxQ.back()])
            {
                maxQ.pop_back();
            }
            maxQ.push_back(i);

            // 2. 出
            while (nums[maxQ.front()] - nums[minQ.front()] > k)
            {
                sumF -= f[left];
                ++left;
                if (minQ.front() < left)
                {
                    minQ.pop_front();
                }
                if (maxQ.front() < left)
                {
                    maxQ.pop_front();
                }
            }

            // 3. 更新答案
            f[i + 1] = sumF % MOD;
        }

        return f[n];
    }
};

class WrongSolution
{
public:
    int countPartitions(std::vector<int>& nums, int k)
    {
        constexpr int MOD = 1'000'000'007;
        int n = nums.size();
        std::vector<long long> f(n + 1, 0);   // f[i]:在给定条件下nums[0, i)的分割数
        std::set<std::pair<int, int>> s;    // <value, index>
        for (int l = 0, r = 0; r < n; ++r)
        {
            while (!s.empty())
            {
                auto it = s.begin();
                int val = it->first, idx = it->second;
                if (idx < l)
                {
                    s.erase(it);
                    continue;
                }

                if (std::abs(val - nums[r]) > k)
                {
                    l = idx + 1;
                    s.erase(it);
                }
                else
                {
                    break;
                }
            }

            while (!s.empty())
            {
                auto it = s.end();
                --it;
                int val = it->first, idx = it->second;
                if (idx < l)
                {
                    s.erase(it);
                    continue;
                }

                if (std::abs(val - nums[r]) > k)
                {
                    l = idx + 1;
                    s.erase(it);
                }
                else
                {
                    break;
                }
            }

            // 滑动窗口[l, r]中的元素满足最大值与最小值之间的差值不超过k
            long long m = r - l + 1;
            f[r + 1] = (f[l] + (1ll + m) * m / 2) % MOD;

            s.emplace(nums[r], r);
        }

        return f[n];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}