#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minProcessingTime(std::vector<int> &processorTime, std::vector<int> &tasks)
    {
        std::sort(processorTime.begin(), processorTime.end());
        std::sort(tasks.begin(), tasks.end(), std::greater<>());

        int ans = 0, n = processorTime.size();
        for (int i = 0; i < n; ++i)
        {
            ans = std::max(ans, processorTime[i] + tasks[i * 4]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
