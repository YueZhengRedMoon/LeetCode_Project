#include <iostream>
#include <vector>

class Solution
{
public:
    void merge(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
    {
        std::vector<int> nums1Copy(nums1.begin(), nums1.begin() + m);
        int index1 = 0, index2 = 0, index = 0;
        while (index1 < m && index2 < n)
        {
            if (nums1Copy[index1] < nums2[index2])
            {
                nums1[index++] = nums1Copy[index1++];
            }
            else
            {
                nums1[index++] = nums2[index2++];
            }
        }

        while (index1 < m)
            nums1[index++] = nums1Copy[index1++];

        while (index2 < n)
            nums1[index++] = nums2[index2++];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
