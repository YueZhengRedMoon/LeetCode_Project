#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int largestSubmatrix(std::vector<std::vector<int>>& matrix)
    {
        int n = matrix[0].size(), ans = 0;
        std::vector<int> heights(n);    // heights[j]:从matrix[i][j]往上有多少个连续的1
        for (const std::vector<int>& row : matrix)  // 枚举子矩形的底边
        {
            for (int j = 0; j < n; ++j)
            {
                int x = row[j];
                if (x == 0)
                {
                    heights[j] = 0;
                }
                else
                {
                    ++heights[j];
                }
            }

            std::vector<int> hs = heights;
            std::sort(hs.begin(), hs.end());
            for (int i = 0; i < n; ++i) // 把 [i,n-1] 作为子数组
            {
                // 子数组长为 n-i，最小值为 hs[i]，对应的子矩形面积为 (n-i)*hs[i]
                ans = std::max(ans, (n - i) * hs[i]);
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int largestSubmatrix(std::vector<std::vector<int>>& matrix)
    {
        int n = matrix[0].size();
        std::vector<int> heights(n);
        std::vector<int> idx(n);    // 按照高度排序后的列号
        std::iota(idx.begin(), idx.end(), 0);
        std::vector<int> nonZeros(n);
        int ans = 0;

        for (const std::vector<int>& row : matrix)  // 枚举子矩形的底边
        {
            int p = 0, q = 0;
            for (int j : idx)
            {
                if (row[j] == 0)
                {
                    heights[j] = 0;
                    idx[p++] = j;   // 高度0排在前面
                }
                else
                {
                    ++heights[j];
                    nonZeros[q++] = j;
                }
            }

            // heights[idx[i]] 是递增的
            for (int i = p; i < n; ++i)
            {
                idx[i] = nonZeros[i - p];   // 把 nonZeros 复制到 idx 的 [p,n-1] 中
                ans = std::max(ans, (n - i) * heights[idx[i]]);
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}