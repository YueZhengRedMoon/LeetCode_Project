#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximizeSquareHoleArea(int n, int m, std::vector<int>& hBars, std::vector<int>& vBars)
    {
        // 贪心地，删的线段越多，面积越大，那就先把所有能删的线段都删掉，计算最大的矩形，长宽分别是多少
        // 取长宽的最小值，即为正方形的边长（多删的线段撤销删除）
        //  - 不删：最长长度是 1
        //  - 删除一条线段：最长长度是 2
        //  - 删除两条编号相邻的线段：最长长度是 3
        //  - 删除三条编号连续的线段（例如 2,3,4）：最长长度是 4
        //  - 依此类推...
        //  - 所以本题要做的是，把数组排序后，求最长连续递增子数组的长度加一

        int side = std::min(f(hBars), f(vBars)) + 1;
        return side * side;
    }

private:
    // 返回 a 排序后的最长连续递增子数组的长度
    int f(std::vector<int>& a)
    {
        std::sort(a.begin(), a.end());
        int len = 1;    // 当前连续递增子数组的长度
        int maxLen = 1;
        for (int i = 1; i < a.size(); ++i)
        {
            if (a[i] == a[i - 1] + 1)
            {
                ++len;
                if (len > maxLen)
                    maxLen = len;
            }
            else
            {
                len = 1;
            }
        }
        return maxLen;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}