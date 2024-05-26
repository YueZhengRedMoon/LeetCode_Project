#include <iostream>
#include <vector>
#include <queue>
#include "debug.h"

class Solution
{
public:
    int kthLargestValue(std::vector<std::vector<int>>& matrix, int k)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::priority_queue<int, std::vector<int>, std::greater<>> minHeap;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int xorSum = matrix[i][j];
                if (i > 0)
                    xorSum ^= matrix[i - 1][j];
                if (j > 0)
                    xorSum ^= matrix[i][j - 1];
                if (i > 0 && j > 0)
                    xorSum ^= matrix[i - 1][j - 1];

                if (minHeap.size() < k)
                {
                    minHeap.push(xorSum);
                }
                else if (xorSum > minHeap.top())
                {
                    minHeap.pop();
                    minHeap.push(xorSum);
                }

                matrix[i][j] = xorSum;
            }
        }
        return minHeap.top();
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> matrix = {{5, 2}, {1, 6}};
    int k = 3;
    int ans = solution.kthLargestValue(matrix, k);
    std::cout << ans << std::endl;
    return 0;
}
