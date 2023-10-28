#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    int search(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = 0, right = n - 1, mid;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (nums[mid] > nums[right])
            {
                // nums[left:mid]是升序排列的
                left = mid + 1;
            }
            else    // nums[mid] < nums[left]
            {
                // nums[mid:right]是升序排列的
                right = mid;
            }
        }
        // nums[0:left-1], nums[left:n)是升序排序的

        int k = left;
        if (k > 0)
        {
            left = 0;
            right = k - 1;
            while (left <= right)
            {
                mid = (left + right) / 2;
                if (nums[mid] > target)
                {
                    right = mid - 1;
                }
                else if (nums[mid] < target)
                {
                    left = mid + 1;
                }
                else
                {
                    return mid;
                }
            }
        }

        left = k;
        right = n - 1;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (nums[mid] > target)
            {
                right = mid - 1;
            }
            else if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                return mid;
            }
        }

        return -1;
    }
};

class Solution2
{
public:
    int search(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[0] <= nums[mid])   // [left:mid]是有序的
            {
                if (nums[0] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else    // [mid:right]是有序的
            {
                if (nums[mid] < target && target <= nums[n - 1])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return -1;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {11};
    int target = 11;
    int ans = solution.search(nums, target);
    logObj(ans);
    return 0;
}
