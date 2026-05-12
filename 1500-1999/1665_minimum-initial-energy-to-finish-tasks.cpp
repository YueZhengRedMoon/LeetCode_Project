#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumEffort(std::vector<std::vector<int>>& tasks)
    {
        // 按照 minimum - actual 从大到小排序
        std::sort(tasks.begin(), tasks.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });
        int ans = 0;
        int s = 0;  // 累计耗费的能量
        for (const std::vector<int>& t : tasks)
        {
            int a = t[0], m = t[1];
            ans = std::max(ans, s + m);
            s += a;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}