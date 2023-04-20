#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

void printDP(std::vector<std::vector<int>> &dp)
{
    for (const auto &row : dp)
    {
        for (const int &value : row)
        {
            if (value == std::numeric_limits<int>::max())
            {
                std::cout << "inf\t";
            }
            else
            {
                std::cout << value << '\t';
            }
        }
        std::cout << std::endl;
    }
}

class Solution
{
public:
    int makeArrayIncreasing(std::vector<int> &arr1, std::vector<int> &arr2)
    {
        std::sort(arr2.begin(), arr2.end());
        auto arr2End = std::unique(arr2.begin(), arr2.end());

        int arr1Size = arr1.size();
        int arr2Size = arr2End - arr2.begin();
        int maxReplace = std::min(arr1Size, arr2Size);
        const int inf = std::numeric_limits<int>::max();

        // 因为要保证严格单调递增，所以不能出现重复的数，所以arr1的最多交换次数为min(arr1Size, arr2Size)
        // dp[i][j]:数组arr1中的前i个元素进行了j次替换后组成严格递增子数组末尾元素的最小值
        std::vector<std::vector<int>> dp(arr1Size + 1,std::vector<int>(maxReplace + 1, inf));
        dp[0][0] = -1;

        int result = -1;
        for (int i = 1; i <= arr1Size; ++i)
        {
            for (int j = 0; j <= std::min(i, maxReplace); ++j)
            {
                // 如果当前元素大于序列的最后一个元素
                if (arr1[i - 1] > dp[i - 1][j])
                {
                    dp[i][j] = arr1[i - 1];
                }
                // 前i - 1个数经过j - 1次替换，变成了严格递增的子数组
                if (j > 0 && dp[i - 1][j - 1] != inf)
                {
                    // 查找严格大于dp[i - 1][j - 1]的最小元素
                    auto it = std::upper_bound(arr2.begin() + j - 1, arr2End, dp[i - 1][j - 1]);
                    if (it != arr2End)
                    {
                        // 找到替换j次使得arr1前i个数组成的子数组满足严格单调递增的末尾最小值
                        dp[i][j] = std::min(dp[i][j], *it);
                    }
                }
                // 如果已经遍历到了arr1，第一个满足dp[i][j]不等于inf的j就是答案
                if (i == arr1Size && dp[i][j] != inf && result == -1)
                {
                    result = j;
                }
            }
        }

        printDP(dp);
        return result;
    }
};

int main()
{
    std::vector<int> arr1 = {1, 5, 3, 6, 7};
    std::vector<int> arr2 = {1, 3, 2, 4};
    Solution solution;
    int result = solution.makeArrayIncreasing(arr1, arr2);
    std::cout << result << std::endl;
    return 0;
}
