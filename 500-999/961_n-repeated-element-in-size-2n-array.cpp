#include <iostream>
#include <vector>
#include <random>
#include <chrono>

class Solution
{
public:
    int repeatedNTimes(std::vector<int>& nums)
    {
        int ans = 0, hp = 0;
        for (int i = 1; i < nums.size(); ++i)
        {
            int x = nums[i];
            if (x == nums[0])
                return x;

            if (hp == 0)
            {
                ans = x;
                hp = 1;
            }
            else
            {
                hp += x == ans ? 1 : -1;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int repeatedNTimes(std::vector<int>& nums)
    {
        for (int i = 1; ; ++i)
        {
            int x = nums[i];
            if (x == nums[i - 1] || (i >= 2 && x == nums[i - 2]) || (i >= 3 && x == nums[i - 3]))
            {
                return x;
            }
        }
    }
};

class Solution3
{
public:
    int repeatedNTimes(std::vector<int>& nums)
    {
        int n = nums.size();
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        while (true)
        {
            // 在 [0, n-1] 中随机生成两个不同下标
            int i = std::uniform_int_distribution<>(0, n - 1)(rng);
            int j = std::uniform_int_distribution<>(0, n - 2)(rng);
            if (j >= i)
            {
                ++j;
            }
            if (nums[i] == nums[j])
            {
                return nums[i];
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}