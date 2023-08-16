#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#include <algorithm>

constexpr int MAX_N = 1e5 + 1;
constexpr int MOD = 1e9 + 7;
int omega[MAX_N];
// 在静态空间代码块中进行预处理，避免每次调用方法时都要预处理
int init = [](){
    for (int i = 2; i < MAX_N; ++i)
    {
        // i是质数
        if (omega[i] == 0)
        {
            for (int j = i; j < MAX_N; j += i)
            {
                ++omega[j]; // i是j的一个质因子
            }
        }
    }
    return 0;
}();

class Solution
{
public:
    int maximumScore(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::vector<int> left(n, -1);   // 质数分数 >= omega[nums[i]]的左侧最近元素的下标
        std::vector<int> right(n, n);   // 质数分数 > omega[nums[i]]的右侧最近元素的下标
        std::stack<int> stack;

        for (int i = 0; i < n; ++i)
        {
            while (!stack.empty() && omega[nums[stack.top()]] < omega[nums[i]])
            {
                right[stack.top()] = i;
                stack.pop();
            }
            if (!stack.empty())
            {
                // 此时如果单调栈不为空，则omega[nums[stack.top()]] >= omega[nums[i]]
                left[i] = stack.top();
            }
            stack.push(i);
        }

        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(), [&](const int i, const int j) { return nums[i] > nums[j];});

        long long ans = 1;
        for (int i : id)
        {
            long long tot = (long long)(i - left[i]) * (right[i] - i);
            if (tot >= k)
            {
                ans = ans * quickPowMod(nums[i], k) % MOD;
                break;
            }
            ans = ans * quickPowMod(nums[i], tot) % MOD;
            k -= tot;
        }

        return (int)ans;
    }

private:
    long long quickPowMod(long long x, long long n)
    {
        long long res = 1;
        while (n)
        {
            if (n & 1)
            {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
