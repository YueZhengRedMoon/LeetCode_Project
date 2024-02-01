#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    std::vector<int> numsGame(std::vector<int> &nums)
    {
        int n = nums.size();
        const int MOD = 1e9 + 7;
        std::vector<int> ans(n, 0);
        long long leftSum = 0, rightSum = 0;
        // 对顶堆，right的堆顶为中位数
        std::priority_queue<int, std::vector<int>, std::less<>> left;       // 维护较小的一半，大顶堆
        std::priority_queue<int, std::vector<int>, std::greater<>> right;   // 维护较大的一半，小顶堆


        for (int i = 0; i < n; ++i)
        {
            int b = nums[i] - i;
            if (i % 2 == 0) // 前缀是奇数，此时left.size() == right.size()
            {
                if (!left.empty() && b < left.top())
                {
                    leftSum -= left.top() - b;  // leftSum = leftSum - left.top() + b
                    left.push(b);
                    b = left.top();
                    left.pop();
                }
                rightSum += b;
                right.push(b);
                ans[i] = (int)((rightSum - right.top() - leftSum) % MOD);
            }
            else    // 前缀是偶数，此时left.size() + 1 == right.size()
            {
                if (b > right.top())
                {
                    rightSum += b - right.top();
                    right.push(b);
                    b = right.top();
                    right.pop();
                }
                leftSum += b;
                left.push(b);
                ans[i] = (int)((rightSum - leftSum) % MOD);
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
