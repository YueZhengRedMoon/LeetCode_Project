#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../debug/debug.h"

/** 错误，需要去重 */
class Solution
{
public:
    using Pair = std::pair<int, std::vector<int>>;
    int kthSmallest(std::vector<std::vector<int>> &mat, int k)
    {
        int m = mat.size(), n = mat[0].size();
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> minHeap;
        Pair pair(0, std::vector<int>(m, 0));
        for (int i = 0; i < m; ++i)
        {
            pair.first += mat[i][0];
        }
        minHeap.emplace(pair);
        for (int i = 0; i < k - 1; ++i)
        {
            Pair top = minHeap.top();
            minHeap.pop();
            for (int j = 0; j < m; ++j)
            {
                std::cout << mat[j][top.second[j]] << ' ';
            }
            std::cout << std::endl;
            for (int j = 0; j < m; ++j)
            {
                int y = top.second[j];
                if (y < n - 1)
                {
                    Pair newPair(top);
                    newPair.first += mat[j][y + 1] - mat[j][y];
                    ++newPair.second[j];
                    minHeap.emplace(std::move(newPair));
                }
            }
        }
        return minHeap.top().first;
    }
};

class Solution2
{
public:
    int kthSmallest(std::vector<std::vector<int>> &mat, int k)
    {
        std::vector<int> a = {0};
        for (auto &row : mat)
        {
            std::vector<int> b;
            b.reserve(a.size() * row.size());
            for (int x : a)
            {
                for (int y : row)
                {
                    b.push_back(x + y);
                }
            }
            std::sort(b.begin(), b.end());
            if (b.size() > k)
            {
                b.resize(k);
            }
            a = std::move(b);
        }
        return a.back();
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat2 = {{1,10,10},{1,4,5},{2,3,6}};
    int k2 = 7;
    int ans2 = solution.kthSmallest(mat2, k2);
    std::cout << ans2 << std::endl;

//    std::vector<std::vector<int>> mat1 = {{1,3,11},{2,4,6}};
//    int k1 = 5;
//    int ans1 = solution.kthSmallest(mat1, k1);
//    std::cout << ans1 << std::endl;
    return 0;
}