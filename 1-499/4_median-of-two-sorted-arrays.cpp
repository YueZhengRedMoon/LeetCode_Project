#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // 确保nums1的长度小于等于nums2的长度
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        int mid1 = 0;   // 前一部分的最大值
        int mid2 = 0;   // 后一部分的最小值

        while (left <= right)   // 此处应该取等号，若不取等号，right应初始化为m+1，且right更新为i
        {
            // 前一部分包含nums1[0,...,i-1]和nums2[0,...,j-1]
            // 后一部分包含nums1[i,...,m-1]和nums2[j,...,n-1]
            // 如果m+n为奇数，则使前一部分多一个元素
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;    // (m + n + 1) / 2等于m + n除以2（向上取值）

            int leftMax1 = (i == 0 ? INT_MIN : nums1[i - 1]);
            int leftMax2 = (j == 0 ? INT_MIN : nums2[j - 1]);
            int rightMin1 = (i == m ? INT_MAX : nums1[i]);
            int rightMin2 = (j == n ? INT_MAX : nums2[j]);

            if (leftMax1 <= rightMin2)
            {
                mid1 = std::max(leftMax1, leftMax2);
                mid2 = std::min(rightMin1, rightMin2);
                left = i + 1;
            }
            else
            {
                right = i - 1;
            }
        }

        return (m + n) % 2 == 0 ? (mid1 + mid2) / 2.0 : mid1;
    }
};

// 不能正确处理存在重复元素的情况
namespace WrongAnswer
{
    class Solution
    {
    public:
        double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
        {
            int cl = -1.0, cr = -1.0;
            int ans = findMedianSortedArrays(nums1, nums2, cl, cr);
            if (ans != -1.0)
                return ans;
            ans = findMedianSortedArrays(nums2, nums1, cl, cr);
            if (ans != -1.0)
                return ans;
            return (cl + cr) / 2.0;
        }

    private:
        double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2, int& cl, int &cr)
        {
            int n = nums1.size();
            int left = 0, right = n;
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                int less = mid;
                int greater = n - less - 1;
                auto it = std::lower_bound(nums2.begin(), nums2.end(), nums1[mid]);
                less += it - nums2.begin();
                greater += nums2.end() - it;

                if (less - greater == -1)
                    cl = nums1[mid];
                else if (less - greater == 1)
                    cr = nums1[mid];

                if (less < greater)
                    left = mid + 1;
                else if (less > greater)
                    right = mid;
                else
                    return nums1[mid];
            }
            return -1.0;
        }
    };
}

int main()
{
    Solution solution;
    std::vector<int> nums1 = {1, 1}, nums2 = {1, 1};
    double ans = solution.findMedianSortedArrays(nums1, nums2);
    std::cout << ans << std::endl;
    return 0;
}
