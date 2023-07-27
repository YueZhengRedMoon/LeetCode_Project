#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        std::unordered_map<int, int> count;
        for (int num : nums)
        {
            ++count[num];
        }
        return count[target] >= (n >> 1) + 1;
    }
};

class Solution2
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size() / 2, count = 0;
        for (int num : nums)
        {
            if (num == target)
            {
                if (++count > n)
                    return true;
            }
            else if (num > target)
            {
                break;
            }
        }
        return false;
    }
};

class Solution3
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0] == target;

        int left = 0, right = n - 1;
        while (left < right)
        {
            if (nums[left] < target)
                ++left;
            else if (nums[left] > target)
                return false;

            if (nums[right] > target)
                --right;
            else if (nums[right] < target)
                return false;

            if (nums[left] == target && nums[right] == target)
                break;
        }

        return (right - left + 1) > n / 2;
    }
};

class Solution4
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        int right = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;
        return (right - left + 1) > n / 2;
    }
};

class Solution5
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if (left == n || nums[left] != target)
            return false;
        int right = left + n / 2;
        return right < n && nums[right] == target;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}