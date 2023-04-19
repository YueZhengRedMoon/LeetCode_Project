#include <iostream>
#include <vector>
#include <unordered_map>

/** 暴力，超时 */
class Solution
{
public:
    int findLength(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        std::unordered_map<int, std::vector<int>> indices;
        indices.reserve(100);

        for (int i = 0; i < nums1.size(); ++i)
        {
            indices[nums1[i]].push_back(i);
        }

        int maxLength = 0;
        for (int i = 0; i < nums2.size(); ++i)
        {
            if (indices.find(nums2[i]) == indices.end())
            {
                continue;
            }

            std::vector<int> &startIndices = indices[nums2[i]];
            for (auto it = startIndices.begin(); it != startIndices.end(); ++it)
            {
                int j = *it;
                int k = i;
                int currentLength = 0;
                while (j < nums1.size() && k < nums2.size() && nums1[j] == nums2[k])
                {
                    ++currentLength;
                    ++j;
                    ++k;
                }
                if (currentLength > maxLength)
                {
                    maxLength = currentLength;
                }
            }
        }

        return maxLength;
    }
};

class Solution2
{
public:
    int findLength(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        // dp[i][j]:以nums1[i-1]为末尾的子数组和以nums2[j-1]为末尾的子数组的最大公共部分长度
        std::vector<std::vector<int>> dp(nums1.size() + 1, std::vector<int>(nums2.size() + 1, 0));

        int result = 0;
        for (int i = 1; i <= nums1.size(); ++i)
        {
            for (int j = 1; j <= nums2.size(); ++j)
            {
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                if (dp[i][j] > result)
                {
                    result = dp[i][j];
                }
            }
        }

        return result;
    }
};

class Solution3
{
public:
    int findLength(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        // dp[i][j]:以nums1[i-1]为末尾的子数组和以nums2[j-1]为末尾的子数组的最大公共部分长度
        std::vector<int> dp(nums2.size() + 1, 0);

        int result = 0;
        for (int i = 1; i <= nums1.size(); ++i)
        {
            for (int j = nums2.size(); j >= 1; --j)
            {
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[j] = dp[j - 1] + 1;
                }
                else
                {
                    dp[j] = 0;
                }
                if (dp[j] > result)
                {
                    result = dp[j];
                }
            }
        }

        return result;
    }
};

class Solution4
{
public:
    int findLength(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        // dp[i][j]:以nums1[i]为末尾的子数组和以nums2[j]为末尾的子数组的最大公共部分长度
        std::vector<std::vector<int>> dp(nums1.size(), std::vector<int>(nums2.size(), 0));

        int result = 0;
        for (int i = 0; i < nums1.size(); ++i)
        {
            for (int j = 0; j < nums2.size(); ++j)
            {
                if (nums1[i] == nums2[j])
                {
                    if (i == 0 || j == 0)
                    {
                        dp[i][j] = 1;
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    }
                    if (dp[i][j] > result)
                    {
                        result = dp[i][j];
                    }
                }
            }
        }

        return result;
    }
};

class Solution5
{
public:
    int findLength(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        // dp[i][j]:以nums1[i]为末尾的子数组和以nums2[j]为末尾的子数组的最大公共部分长度
        std::vector<int> dp(nums2.size(), 0);

        int result = 0;
        for (int i = 0; i < nums1.size(); ++i)
        {
            for (int j = nums2.size() - 1; j >= 0; --j)
            {
                if (nums1[i] == nums2[j])
                {
                    if (i == 0 || j == 0)
                    {
                        dp[j] = 1;
                    }
                    else
                    {
                        dp[j] = dp[j - 1] + 1;
                    }
                    if (dp[j] > result)
                    {
                        result = dp[j];
                    }
                }
                else
                {
                    dp[j] = 0;
                }
            }
        }

        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}