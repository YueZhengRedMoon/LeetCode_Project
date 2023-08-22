#include <iostream>
#include <vector>

class Solution
{
public:
    int maxDistToClosest(std::vector<int> &seats)
    {
        int n = seats.size(), ans = 0;
        int last = -1;  // 上一个有人做的位置
        int i;
        // 坐在最左边的情况
        for (i = 0; i < n; ++i)
        {
            if (seats[i] == 1)
            {
                ans = i;
                last = i;
                ++i;
                break;
            }
        }
        // 坐在中间的情况
        for (; i < n; ++i)
        {
            if (seats[i] == 1)
            {
                ans = std::max((i - last) / 2, ans);
                last = i;
            }
        }
        // 坐在最右边的情况
        ans = std::max(n - 1 - last, ans);
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
