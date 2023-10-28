#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include "../debug/debug.h"

class Solution
{
public:
    int minLengthAfterRemovals(std::vector<int> &nums)
    {
        int n = nums.size();
        int x = nums[n / 2];
        int maxCnt = std::upper_bound(nums.begin(), nums.end(), x) - std::lower_bound(nums.begin(), nums.end(), x);
        return std::max(maxCnt * 2 - n, n % 2);
    }
};

class Solution2
{
public:
    int minLengthAfterRemovals(std::vector<int> &nums)
    {
        std::unordered_map<int, int> count;
        for (int num : nums)
            ++count[num];

        std::priority_queue<int, std::vector<int>, std::less<>> maxHeap;
        for (auto [num, c] : count)
            maxHeap.push(c);

        while (maxHeap.size() >= 2)
        {
            int top1 = maxHeap.top();
            maxHeap.pop();
            int top2 = maxHeap.top();
            maxHeap.pop();
            int top3 = maxHeap.empty() ? 0 : maxHeap.top();

            int delCnt = std::max(top2 - top3, 1);
            top1 -= delCnt;
            top2 -= delCnt;

            if (top1)
                maxHeap.push(top1);
            if (top2)
                maxHeap.push(top2);
        }

        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,3,4,9};
    int ans = solution.minLengthAfterRemovals(nums);
    logObj(ans);
    return 0;
}
