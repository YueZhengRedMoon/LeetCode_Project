#include <iostream>
#include <vector>

class Solution
{
public:
    int sumIndicesWithKSetBits(std::vector<int> &nums, int k)
    {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (setCount(i) == k)
                ans += nums[i];
        }
        return ans;
    }

private:
    int setCount(int n)
    {
        int cnt = 0;
        while (n)
        {
            ++cnt;
            n &= n - 1;
        }
        return cnt;
    }
};

class Solution2
{
public:
    int sumIndicesWithKSetBits(std::vector<int> &nums, int k)
    {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (__builtin_popcount(i) == k)
                ans += nums[i];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}