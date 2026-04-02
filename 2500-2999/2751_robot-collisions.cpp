#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    std::vector<int> survivedRobotsHealths(std::vector<int>& positions, std::vector<int>& healths, std::string directions)
    {
        int n = positions.size();

        // 机器人的编号
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);

        // 将机器人按照位置从左到右排序
        std::sort(idx.begin(), idx.end(), [&](int a, int b) {return positions[a] < positions[b];});

        std::vector<int> stack;
        for (int i : idx)
        {
            int& rightHP = healths[i];
            char rightDir = directions[i];
            while (!stack.empty() && rightHP > 0)
            {
                int j = stack.back();
                int& leftHP = healths[j];
                char leftDir = directions[j];

                // 相撞
                if (leftDir == 'R' && rightDir == 'L')
                {
                    if (leftHP < rightHP)
                    {
                        // leftHP = 0;
                        stack.pop_back();
                        --rightHP;
                    }
                    else if (leftHP > rightHP)
                    {
                        rightHP = 0;
                        --leftHP;
                    }
                    else    // leftHP == rightHP
                    {
                        // leftHP = 0;
                        rightHP = 0;
                        stack.pop_back();
                    }
                }
                else    // 两个机器人移动方向相同或背向移动，不会相撞
                {
                    break;
                }
            }

            if (rightHP > 0)
            {
                stack.push_back(i);
            }
        }

        std::sort(stack.begin(), stack.end());  // 剩余的机器人按照编号排序
        std::vector<int> ans(stack.size());
        for (int i = 0; i < stack.size(); ++i)
        {
            ans[i] = healths[stack[i]];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}