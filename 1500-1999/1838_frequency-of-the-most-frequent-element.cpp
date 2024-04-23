#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int maxFrequency(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());

        std::vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = prefix[i] + nums[i];

        // 检查是否可以通过k次操作使排序后的nums中存在一个区间nums[l, r)使得区间中所有元素都为nums[r-1]
        auto check = [&nums, &prefix, &n](long long len, int k) -> bool {
            for (int l = 0, r = len; r <= n; ++l, ++r)
            {
                if (len * nums[r - 1] - (prefix[r] - prefix[l]) <= k)
                    return true;
            }
            return false;
        };

        int left = 1, right = n, ans = 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(mid, k))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return ans;
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        int maxFrequency(std::vector<int>& nums, int k)
        {
            std::unordered_map<int, int> f; // 每种数的频率
            for (int num : nums)
            {
                ++f[num];
            }

            int maxFF = 0;  // 最高频元素的频数
            std::unordered_map<int, std::vector<int>> ff;   // 频数的频数
            for (auto [num, cnt] : f)
            {
                ff[cnt].push_back(num);
                if (cnt > maxFF)
                    maxFF = cnt;
            }

            // 对nums数组排序去重
            std::sort(nums.begin(), nums.end());
            int n = std::unique(nums.begin(), nums.end()) - nums.begin();
            std::unordered_map<int, int> idx;   // 每个元素排序去重后的顺序
            for (int i = 0; i < n; ++i)
            {
                idx[nums[i]] = i;
            }

            int ans = maxFF;
            for (auto it = ff.begin(); it != ff.end(); ++it)
            {
                int frequency = it->first;
                std::vector<int>& freqNum = it->second;
                for (int num : freqNum)
                {
                    int cnt = frequency;   // num的频数
                    int opCnt = k;         // 剩余的操作次数
                    // 将小于num的元素通过k次操作加到num
                    for (int i = idx[num] - 1; i >= 0 && opCnt; --i)
                    {
                        int delta = std::min(f[nums[i]], opCnt / (num - nums[i]));  // num频数的增加量
                        cnt += delta;
                        opCnt -= delta * (num - nums[i]);
                    }
                    if (cnt > ans)
                        ans = cnt;
                }
            }

            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
