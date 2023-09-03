#include <iostream>
#include <vector>
#include <functional>
#include "debug.h"

class Solution
{
public:
    int minOperations(std::vector<int> &nums, int target)
    {
        std::vector<int> count(32, 0);
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
            ++count[__builtin_ctz(num)];
        }

        if (sum < target)
            return -1;
        if (sum == target)
            return 0;

        std::function<bool(int)> backtracking = [&](int i){
            if (count[i] > 0)
            {
                --count[i];
                return true;
            }
            if (i == 0)
                return false;

            --i;
            int temp = count[i];
            if (backtracking(i) && backtracking(i))
            {
                return true;
            }

            count[i] = temp;
            return false;
        };

        int ans = 0, i = 0;
        while (target > 0)
        {
            if (target & 1)
            {
                // 不可以通过已有的数凑出2^i
                if (!backtracking(i))
                {
                    bool success = false;
                    for (int j = i + 1; j < 32; ++j)
                    {
                        if (count[j] > 0)
                        {
                            success = true;
                            int k = j;
                            while (k > i)
                            {
                                --count[k];
                                --k;
                                count[k] += 2;
                                ++ans;
                            }
                            --count[k];
                            break;
                        }
                    }
                    if (!success)
                        return -1;
                }
            }
            ++i;
            target >>= 1;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,1,16,1,64,1,1,32,1};
    int target = 8;
    int ans = solution.minOperations(nums, target);
    logObj(ans);
    return 0;
}
