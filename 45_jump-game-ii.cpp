#include <iostream>
#include <vector>

class Solution
{
public:
    int jump(std::vector<int> &nums)
    {
        int curDistance = 0;    // 当前覆盖最远距离下标
        int ans = 0;            // 记录走的最大步数
        int nextDistance = 0;   // 下一步覆盖最远距离下标
        for (int i = 0; i < nums.size(); ++i)
        {
            // 更新下一步覆盖最远距离下标
            nextDistance = std::max(nums[i] + i, nextDistance);

            if (i == curDistance)
            {
                if (curDistance < nums.size() - 1)
                {
                    std::cout << "从" << curDistance << "走到" << std::min(nextDistance, static_cast<int>(nums.size()) - 1) << std::endl;
                    ++ans;
                    curDistance = nextDistance;
                    // 下一步的覆盖范围已经可以到达终点，结束循环
                    if (nextDistance >= nums.size() - 1)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int jump(std::vector<int> &nums)
    {
        int curDistance = 0;    // 当前覆盖最远距离下标
        int ans = 0;            // 记录走的步数
        int nextDistance = 0;   // 下一步覆盖的最远距离下标
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            nextDistance = std::max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
            if (i == curDistance)
            {
                curDistance = nextDistance;
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    // 15 7 0 9 6 9 6 1 7 9 0 1 2 9 0 3
    std::vector<int> nums;
    int n, num;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        nums.push_back(num);
    }

    Solution solution;
    std::cout << solution.jump(nums) << std::endl;
    return 0;
}
