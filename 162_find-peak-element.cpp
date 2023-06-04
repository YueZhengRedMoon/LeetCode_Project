#include <iostream>
#include <vector>

class Solution
{
public:
    int findPeakElement(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1) return 0;
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = (left + right) >> 1;
            if (mid == 0)
            {
                if (nums[0] > nums[1])
                    return 0;
                left = mid + 1;
            }
            else if (mid == n - 1)
            {
                if (nums[mid - 1] < nums[mid])
                    return mid;
                right = mid - 1;
            }
            else if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1])
            {
                return mid;
            }
            else if (nums[mid - 1] < nums[mid] && nums[mid] < nums[mid + 1])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return 0;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}