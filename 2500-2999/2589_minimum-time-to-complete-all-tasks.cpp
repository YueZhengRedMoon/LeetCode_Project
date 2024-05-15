#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findMinimumTime(std::vector<std::vector<int>>& tasks)
    {
        std::sort(tasks.begin(), tasks.end(), [](const auto& a, const auto&b) -> bool {return a[1] < b[1];});
        int ans = 0;
        std::vector<bool> run(tasks.back()[1] + 1);
        for (const auto& t : tasks)
        {
            int start = t[0], end = t[1], d = t[2];
            d -= std::count_if(run.begin() + start, run.begin() + end + 1, [](bool r) -> bool {return r;}); // 去掉运行中的时间点
            for (int i = end; d > 0; --i)
            {
                if (!run[i])
                {
                    run[i] = true;
                    --d;
                    ++ans;
                }
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
