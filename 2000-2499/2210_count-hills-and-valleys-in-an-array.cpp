#include <iostream>
#include <vector>

class Solution1
{
public:
    int countHillValley(std::vector<int>& nums)
    {
        int n = nums.size(), m = 1, ans = 0;
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] != nums[i - 1])
            {
                nums[m++] = nums[i];
            }
        }

        for (int i = 1; i < m - 1; ++i)
        {
            ans +=  (nums[i - 1] < nums[i]) == (nums[i] > nums[i + 1]);
        }
        return ans;
    }
};

class Solution2
{
public:
    int countHillValley(std::vector<int>& nums)
    {
        int ans = 0;
        int preState = 0;
        for (int i = 0; i + 1 < nums.size(); ++i)
        {
            int x = nums[i], y = nums[i + 1];
            if (x > y)
            {
                if (preState == -1) // x是峰
                {
                    ++ans;
                }
                preState = 1;
            }
            else if (x < y)
            {
                if (preState == 1)  // x是谷
                {
                    ++ans;
                }
                preState = -1;
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
