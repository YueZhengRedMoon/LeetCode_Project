#include <iostream>
#include <vector>

class Solution
{
public:
    bool isTrionic(std::vector<int>& nums)
    {
        if (nums[0] >= nums[1]) // 一开始必须是递增的
        {
            return false;
        }

        int cnt = 1;    // 拐弯次数
        for (int i = 2; i < nums.size(); ++i)
        {
            if (nums[i - 1] == nums[i]) // 出现相邻相等元素，不是三段式数组
            {
                return false;
            }

            if ((nums[i - 2] < nums[i - 1]) != (nums[i - 1] < nums[i]))
            {
                ++cnt;
            }
        }
        return cnt == 3;
    }
};

class MySolution
{
public:
    bool isTrionic(std::vector<int>& nums)
    {
        int n = nums.size(), p = -1, q = -1;
        int trend = 1;  // 当前的趋势，1:正在递增；-1:正在递减
        for (int i = 1; i < n; ++i)
        {
            if (nums[i - 1] > nums[i])  // 递减
            {
                if (trend == 1) // 此前正在递增
                {
                    if (p == -1)    // 第一次开始递减
                    {
                        p = i - 1;
                    }
                    else    // 出现了第二次递减拐点，不是三段式数组
                    {
                        return false;
                    }
                }
                // no else，此前正在递减，现在继续保持递减

                trend = -1; // 当前的趋势是递减
            }
            else if (nums[i - 1] < nums[i]) // 递增
            {
                if (trend == -1)    // 此前正在递减
                {
                    q = i;
                }
                // no else，此前正在递增，现在继续保持递增

                trend = 1;  // 当前的趋势是递增
            }
            else    // nums[i - 1] == nums[i]，出现相邻相等元素，不是三段式数组
            {
                return false;
            }
        }

        return trend == 1 && 0 < p && p < q;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}