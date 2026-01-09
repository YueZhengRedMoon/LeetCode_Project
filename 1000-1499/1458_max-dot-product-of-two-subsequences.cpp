#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxDotProduct(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int len1 = nums1.size(), len2 = nums2.size();
        // f[i][j]:nums1[0, i]和nums2[j]中包含nums1[i], nums2[j]的非空子序列的最大点积
        std::vector<std::vector<int>> f(len1, std::vector<int>(len2));
        // maxF[i][j]: f[0, i][0, j]中的最大值
        std::vector<std::vector<int>> maxF(len1, std::vector<int>(len2));

        // 初始化，子序列中只有1个元素的场景
        maxF[0][0] = nums1[0] * nums2[0];
        for (int i = 1; i < len1; ++i)
        {
            f[i][0] = nums1[i] * nums2[0];
            maxF[i][0] = std::max(f[i][0], maxF[i - 1][0]);
        }
        for (int j = 1; j < len2; ++j)
        {
            f[0][j] = nums1[0] * nums2[j];
            maxF[0][j] = std::max(f[0][j], maxF[0][j - 1]);
        }

        for (int i = 1; i < len1; ++i)
        {
            for (int j = 1; j < len2; ++j)
            {
                f[i][j] = nums1[i] * nums2[j] + std::max(maxF[i - 1][j - 1], 0);
                maxF[i][j] = std::max({maxF[i - 1][j], maxF[i][j - 1], f[i][j]});
            }
        }
        return maxF[len1 - 1][len2 - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}