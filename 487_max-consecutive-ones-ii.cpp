#include <iostream>
#include <vector>

class Solution
{
public:
    int findMaxConsecutiveOnes(std::vector<int> &nums)
    {
        int ans = 0;
        int lastBegin = -3, lastEnd = -3;
        int i, n = nums.size();
        int begin = n + 1;
        for (i = 0; i < n; ++i)
        {
            if (nums[i] == 1)
            {
                begin = i;
                break;
            }
        }
        nums.push_back(0);
        for (i = begin + 1; i <= n; ++i)
        {
            if (nums[i] == 0 && begin != -1)
            {
                if (lastEnd + 2 == begin)
                {
                    ans = std::max(ans, i - lastBegin);
                }
                else
                {
                    ans = std::max(ans, i - begin + 1);
                }
                lastBegin = begin;
                lastEnd = i - 1;
                begin = -1;
            }
            else if (nums[i] == 1 && begin == -1)
            {
                begin = i;
            }
        }
        if (ans == 0)
            ans = 1;
        else if (ans > n)
            ans = n;
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}