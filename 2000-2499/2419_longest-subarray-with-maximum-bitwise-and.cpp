#include <iostream>
#include <vector>

class Solution
{
public:
    int longestSubarray(std::vector<int>& nums)
    {
        int maxVal = 0, ans = 0, cur = 0;
        for (int x : nums)
        {
            if (x > maxVal)
            {
                maxVal = x;
                cur = 1;
                ans = 0;
            }
            else if (x == maxVal)
            {
                ++cur;
            }
            else
            {
                if (cur > ans)
                    ans = cur;
                cur = 0;
            }
        }
        if (cur > ans)
            ans = cur;

        return ans;
    }
};
int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
