#include <iostream>
#include <vector>
#include <map>

class Solution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        int ans = 0;
        int top = -1;   // 栈顶下标，把nums当作栈
        for (int x : nums)
        {
            while (top >= 0 && x < nums[top])
            {
                --top;  // 出栈
                ++ans;
            }
            // 如果 x 与栈顶相同，那么 x 与栈顶可以在同一次操作中都变成 0，x 无需入栈
            if (top < 0 || x != nums[top])
            {
                nums[++top] = x;    // 入栈
            }
        }
        return ans + top + (nums[0] > 0);
    }
};

class WrongSolution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        std::map<int, std::vector<std::pair<int, int>>> levels;
        for (int i = 0; i < nums.size(); ++i)
        {
            int x = nums[i];
            std::vector<std::pair<int, int>>& level = levels[x];
            if (level.empty() || level.back().second + 1 != i)
            {
                level.emplace_back(i, i);
            }
            else
            {
                level.back().second = i;
            }
        }

        int ans = levels.begin()->first == 0 ? 0 : 1;
        auto it = levels.begin();
        for (++it; it != levels.end(); ++it)
        {
            ans += it->second.size();
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}