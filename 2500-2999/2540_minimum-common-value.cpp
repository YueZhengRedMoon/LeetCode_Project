#include <iostream>
#include <vector>

class Solution
{
public:
    int getCommon(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int n = nums1.size(), m = nums2.size(), i = 0, j = 0;
        while (i < n && j < m)
        {
            while (i < n && nums1[i] < nums2[j])
                ++i;
            while (i < n && j < m && nums2[j] < nums1[i])
                ++j;
            if (i < n && j < m && nums1[i] == nums2[j])
            {
                return nums1[i];
            }
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}