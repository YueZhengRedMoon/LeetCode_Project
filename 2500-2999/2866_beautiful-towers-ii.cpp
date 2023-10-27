#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    long long maximumSumOfHeights(std::vector<int> &maxHeights)
    {
        int n = maxHeights.size();
        std::vector<long long> suf(n + 1, 0);
        std::stack<long long> stack({n});
        long long sum = 0;

        for (int i = n - 1; i >= 0; --i)
        {
            long long x = maxHeights[i];
            while (stack.size() > 1 && x <= maxHeights[stack.top()])
            {
                int j = stack.top();
                stack.pop();
                sum -= (long long) maxHeights[j] * (stack.top() - j);
            }
            sum += x * (stack.top() - i);
            suf[i] = sum;
            stack.push(i);
        }

        long long pre = 0, ans = sum;
        stack = std::stack<long long>({-1});
        for (int i = 0; i < n; ++i)
        {
            long long x = maxHeights[i];
            while (stack.size() > 1 && x <= maxHeights[stack.top()])
            {
                int j = stack.top();
                stack.pop();
                pre -= (long long) maxHeights[j] * (j - stack.top());
            }
            pre += x * (i - stack.top());
            ans = std::max(ans, pre + suf[i + 1]);
            stack.push(i);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
