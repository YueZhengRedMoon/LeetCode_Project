#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    int unequalTriplets(std::vector<int> &nums)
    {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n - 2; ++i)
        {
            for (int j = i + 1; j < n - 1; ++j)
            {
                if (nums[i] == nums[j]) continue;
                for (int k = j + 1; k < n; ++k)
                {
                    if (nums[k] != nums[i] && nums[k] != nums[j])
                    {
                        ++ans;
                    }
                }
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int unequalTriplets(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for (int i = 0, j = 0; i < n; i = j)
        {
            while (j < n && nums[j] == nums[i])
            {
                ++j;
            }
            ans += i * (j - i) * (n - j);
        }
        return ans;
    }
};

class Solution3
{
public:
    int unequalTriplets(std::vector<int> &nums)
    {
        std::unordered_map<int, int> count;
        for (int num : nums)
        {
            ++count[num];
        }
        int ans = 0, n = nums.size(), t = 0;
        for (auto [_, v] : count)
        {
            ans += t * v * (n - t - v);
            t += v;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}