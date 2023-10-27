#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int minOperations(std::vector<int> &nums, int k)
    {
        int ans = 0, n = nums.size();
        std::unordered_set<int> set;
        for (int i = n - 1; i >= 0; --i)
        {
            ++ans;
            if (nums[i] <= k)
            {
                set.insert(nums[i]);
                if (set.size() == k)
                    break;
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
