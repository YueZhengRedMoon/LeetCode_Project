#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<double> sampleStats(std::vector<int> &count)
    {
        int n = count.size();
        int minVal = -1;
        int maxVal = 0;
        int total = 0;  // 样本总数
        double sum = 0;    // 样本总和
        int mode = 0;
        for (int i = 0; i < n; ++i)
        {
            if (count[i] != 0)
            {
                if (minVal == -1)
                {
                    minVal = i;
                }
                maxVal = i;
                total += count[i];
                sum += static_cast<double>(count[i]) * i;
                if (count[i] > count[mode])
                {
                    mode = i;
                }
            }
        }
        double mean = sum / total;
        int half = total / 2;
        int j = 0;
        double median = 0;
        for (int i = 0; i < n; ++i)
        {
            if (count[i] != 0)
            {
                j += count[i];
                if (j >= half)
                {
                    if (total % 2 == 0)
                    {
                        if (j > half)
                        {
                            median = i;
                        }
                        else
                        {
                            int k = i;
                            for (k = i + 1; k < n && count[k] == 0; ++k);
                            median = (i + k) / 2.0;
                        }
                    }
                    else
                    {
                        if (j > half)
                        {
                            median = i;
                        }
                        else
                        {
                            int k = i;
                            for (k = i + 1; k < n && count[k] == 0; ++k);
                            median = k;
                        }
                    }
                    break;
                }
            }
        }
        return {static_cast<double>(minVal), static_cast<double>(maxVal), mean, median, static_cast<double>(mode)};
    }
};

int main()
{
    Solution solution;
    std::vector<int> count = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,
                              0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              0,0,0,0};
    std::vector<double> ans = solution.sampleStats(count);
    debug::printVector(ans);
    return 0;
}