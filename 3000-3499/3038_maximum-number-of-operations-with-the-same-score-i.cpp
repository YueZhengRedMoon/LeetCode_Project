#include <iostream>
#include <vector>

class Solution
{
public:
    int maxOperations(std::vector<int>& nums)
    {
        int n = nums.size(), ans = 1, score = nums[0] + nums[1];
        for (int i = 3; i < n; i += 2)
        {
            if (nums[i] + nums[i - 1] == score)
                ++ans;
            else
                break;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
