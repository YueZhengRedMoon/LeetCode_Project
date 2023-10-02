#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<int> colorTheArray(int n, std::vector<std::vector<int>> &queries)
    {
        std::vector<int> colors(n, 0);
        std::vector<int> answer(queries.size());
        int same = 0;
        for (int i = 0; i < queries.size(); ++i)
        {
            int index = queries[i][0];
            int oldColor = colors[index];
            colors[index] = queries[i][1];
            // 颜色没有发生变化
            if (colors[index] == oldColor)
            {
                answer[i] = same;
                continue;
            }
            // 考虑前一个颜色
            if (index > 0)
            {
                if (colors[index - 1] == colors[index] && colors[index] != 0)
                {
                    ++same;
                }
                else if (colors[index - 1] == oldColor && oldColor != 0)
                {
                    --same;
                }
            }
            // 考虑后一个颜色
            if (index < n - 1)
            {
                if (colors[index] == colors[index + 1] && colors[index] != 0)
                {
                    ++same;
                }
                else if (oldColor == colors[index + 1] && oldColor != 0)
                {
                    --same;
                }
            }
            answer[i] = same;
        }

        debug::printVector(colors);
        return answer;
    }
};

int main()
{
    Solution solution;
    int n = 4;
    std::vector<std::vector<int>> queries = {{0,2}, {1, 2}, {3, 1}, {1, 1}, {2, 1}};
    auto answer = solution.colorTheArray(n, queries);
    debug::printVector(answer);
    return 0;
}
