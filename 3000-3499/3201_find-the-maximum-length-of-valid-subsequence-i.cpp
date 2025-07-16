#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumLength(std::vector<int>& nums)
    {
        int cnt0 = 0, cnt1 = 0, len01 = 0, len10 = 0;
        bool flag01 = false;    // 已有0101...子序列中的最后一位是否为0
        bool flag10 = false;    // 已有1010...子序列中的最后一位是否为1
        for (int x : nums)
        {
            if (x % 2 == 0)
            {
                ++cnt0;
                if (flag10)
                {
                    ++len10;
                    flag10 = false;
                }
                if (!flag01)
                {
                    flag01 = true;
                    ++len01;
                }
            }
            else    // x % 2 == 1
            {
                ++cnt1;
                if (flag01)
                {
                    ++len01;
                    flag01 = false;
                }
                if (!flag10)
                {
                    flag10 = true;
                    ++len10;
                }
            }
        }
        return std::max({cnt1, cnt0, len01, len10});
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
