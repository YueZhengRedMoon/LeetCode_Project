#include <iostream>
#include <vector>

class Solution
{
public:
    int maxDistance(std::vector<int>& colors)
    {
        int n = colors.size();
        int c = colors[0];
        if (c != colors[n - 1])
        {
            return n - 1;
        }

        // 找最右边的颜色不等于 c 的房子，题目保证至少有两栋颜色不同的房子
        int r = n - 2;
        while (colors[r] == c)
        {
            --r;
        }

        // 找最左边的颜色不等于 c 的房子
        int l = 1;
        while (colors[l] == c)
        {
            ++l;
        }

        return std::max(r, n - 1 - l);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}