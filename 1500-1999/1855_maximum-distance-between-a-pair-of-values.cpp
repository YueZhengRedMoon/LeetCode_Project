#include <iostream>
#include <vector>

class Solution
{
public:
    int maxDistance(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int n = nums1.size(), m = nums2.size(), ans = 0;
        for (int i = 0; i < std::min(n, m); ++i)
        {
            // 二分查找递减数组nums2[i,m)中最小的>=nums1[i]的数nums2[j]
            int left = i, right = m, j = -1;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (nums1[i] <= nums2[mid])
                {
                    j = mid;
                    left = mid + 1;
                }
                else    // nums1[i] > nums2[mid]
                {
                    right = mid;
                }
            }
            if (j != -1)
            {
                ans = std::max(ans, j - i);
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int maxDistance(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int ans = 0, i = 0;
        for (int j = 0; j < nums2.size(); ++j)
        {
            while (i < nums1.size() && nums1[i] > nums2[j])
            {
                ++i;
            }
            if (i == nums1.size())
            {
                break;
            }
            ans = std::max(ans, j - i);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}