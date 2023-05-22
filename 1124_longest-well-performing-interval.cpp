#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    int longestWPI(std::vector<int> &hours)
    {
        int n = hours.size();
        std::vector<int> prefix(n + 1);
        std::stack<int> stack;
        prefix[0] = 0;
        stack.push(0);
        for (int j = 1; j <= n; ++j)
        {
            prefix[j] = prefix[j - 1] + (hours[j - 1] > 8 ? 1 : -1);
            if (prefix[j] < prefix[stack.top()])
            {
                stack.push(j);
            }
        }
        int ans = 0;
        for (int i = n; i > 0; --i)
        {
            while (!stack.empty() && prefix[i] > prefix[stack.top()])
            {
                ans = std::max(i - stack.top(), ans);
                stack.pop();
            }
            if (stack.empty())
            {
                break;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int longestWPI(std::vector<int> &hours)
    {
        int n = hours.size(), ans = 0, s = 0;
        std::vector<int> pos(n + 2, 0);    // 记录前缀和首次出现的位置
        for (int i = 1; i <= n; ++i)
        {
            hours[i - 1] > 8 ? --s : ++s;   // 所有前缀和相关的都取反
            // 当前前缀和大于0，因此最大长度即为i
            if (s < 0)
            {
                ans = i;
            }
            else
            {
                if (pos[s + 1])
                {
                    ans = std::max(ans, i - pos[s + 1]);
                }
                if (pos[s] == 0)
                {
                    // 前缀和s首次出现的位置为i
                    pos[s] = i;
                }
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
