#include <iostream>
#include <vector>

class Solution
{
public:
    int earliestFinishTime(std::vector<int>& landStartTime, std::vector<int>& landDuration,
                           std::vector<int>& waterStartTime, std::vector<int>& waterDuration)
    {
        int landWater = solve(landStartTime, landDuration, waterStartTime, waterDuration);
        int waterLand = solve(waterStartTime, waterDuration, landStartTime, landDuration);
        return std::min(landWater, waterLand);
    }

private:
    int solve(std::vector<int>& startTime1, std::vector<int>& duration1,
              std::vector<int>& startTime2, std::vector<int>& duration2)
    {
        int minFinish = INT_MAX, n = startTime1.size(), m = startTime2.size();
        for (int i = 0; i < n; ++i)
        {
            minFinish = std::min(minFinish, startTime1[i] + duration1[i]);
        }
        int res = INT_MAX;
        for (int i = 0; i < m; ++i)
        {
            res = std::min(res, std::max(minFinish, startTime2[i]) + duration2[i]);
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}