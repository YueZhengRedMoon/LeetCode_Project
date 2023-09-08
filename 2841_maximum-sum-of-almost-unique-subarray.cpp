#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    long long maxSum(std::vector<int> &nums, int m, int k)
    {
        int n = nums.size();
        std::unordered_map<int, int> count;
        count.reserve(k);
        long long sum = 0, ans = 0;
        for (int i = 0; i < k; ++i)
        {
            ++count[nums[i]];
            sum += nums[i];
        }
        if (count.size() >= m)
        {
            ans = sum;
        }

        for (int i = 0, j = k; j < n; ++i, ++j)
        {
            sum += nums[j] - nums[i];
            auto it = count.find(nums[i]);
            if (--(it->second) == 0)
            {
                count.erase(it);
            }
            ++count[nums[j]];
            if (sum > ans && count.size() >= m)
            {
                ans = sum;
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
