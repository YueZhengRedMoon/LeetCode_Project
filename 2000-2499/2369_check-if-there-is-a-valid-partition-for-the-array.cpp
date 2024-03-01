#include <iostream>
#include <vector>

class Solution
{
public:
    bool validPartition(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<bool> f(3, false);  // f[i]:nums[0,i)是否存在有效划分
        f[0] = true;
        f[2] = nums[0] == nums[1];

        for (int i = 3; i <= n; ++i)
        {
            int cur = i % 3, last1 = (i - 2) % 3, last2 = (i - 3) % 3;
            if (f[last1] && nums[i - 2] == nums[i - 1])
            {
                f[cur] = true;
            }
            else if (f[last2])
            {
                if (nums[i - 3] == nums[i - 2] && nums[i - 2] == nums[i - 1])
                    f[cur] = true;
                else if (nums[i - 3] + 1 == nums[i - 2] && nums[i - 2] + 1 == nums[i - 1])
                    f[cur] = true;
                else
                    f[cur] = false;
            }
            else
            {
                f[cur] = false;
            }
        }

        return f[n % 3];
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {348054,7876,34051};
    bool ans = solution.validPartition(nums);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
