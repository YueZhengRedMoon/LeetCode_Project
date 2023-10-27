#include <iostream>
#include <vector>
#include <deque>

class Solution
{
public:
    long long maximumTripletValue(std::vector<int> &nums)
    {
        const int inf = 0x39C5BB;
        int n = nums.size();
        std::vector<int> rightMin(n), rightMax(n);
        rightMin[n - 1] = inf;
        rightMax[n - 1] = -inf;
        for (int i = n - 2; i >= 0; --i)
        {
            rightMax[i] = std::max(nums[i + 1], rightMax[i + 1]);
            rightMin[i] = std::min(nums[i + 1], rightMin[i + 1]);
        }

        long long ans = 0;
        std::deque<int> incStack({nums[0]}), decStack({nums[0]});
        for (int i = 1; i < n; ++i)
        {
            // 单调递增栈
            while (!incStack.empty() && incStack.back() > nums[i])
                incStack.pop_back();
            incStack.push_back(nums[i]);
            if (incStack.size() >= 2 && rightMin[i] < 0)
                ans = std::max(ans, (long long) (incStack.front() - incStack.back()) * rightMin[i]);

            // 单调递减栈
            while (!decStack.empty() && decStack.back() < nums[i])
                decStack.pop_back();
            decStack.push_back(nums[i]);
            if (decStack.size() >= 2 && rightMax[i] > 0)
                ans = std::max(ans, (long long) (decStack.front() - decStack.back()) * rightMax[i]);
        }

        return ans;
    }
};

// 枚举k
class Solution2
{
public:
    long long maximumTripletValue(std::vector<int> &nums)
    {
        long long ans = 0, maxDiff = 0, preMax = 0;
        for (int num : nums)
        {
            ans = std::max(ans, maxDiff * num);
            maxDiff = std::max(maxDiff, preMax - num);
            if (num > preMax) preMax = num;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
