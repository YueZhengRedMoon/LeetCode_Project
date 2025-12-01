#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    long long maxRunTime(int n, std::vector<int>& batteries)
    {
        int m = batteries.size();

        // 假设最多可以让n台电脑同时运行k分钟，则一个构建一个k*n的表A
        // 其中A[i][j]=x表示在第i分钟，第j台电脑由电池x供电(0<=x<m, m=batteries.size())
        // 根据题意可以得到以下限制：
        //  1.同一行的元素必须互不相同，既在某一分钟内，所有n台电脑使用的电池都不相同
        //  2.每一个在[0, m)范围内的数x的出现次数不能超过对应的batteries[x]
        //  3.x的出现次数不能超过k，若超过k则会导致某一行出现多个x，不符合限制1
        // 因此有x的出现次数<= min(batteries[x], k)，既每个电池最多只能供电min(batteries[x], k)分钟
        // 二分答案k，检查是否可以使n台电脑运行k分钟，对于电量>k的电池，其只能使用一次，多余的电量会被浪费

        long long ans = 0;
        long long left = 0, right = (std::accumulate(batteries.begin(), batteries.end(), 0ll) / n) + 1;
        while (left < right)
        {
            long long k = left + (right - left) / 2;
            long long total = 0;
            long long target = n * k;
            for (int x = 0; x < m && total < target; ++x)
            {
                total += std::min<long long>(batteries[x], k);
            }

            if (total >= target)    // 可以让n台电脑同时运行k分钟
            {
                ans = k;
                left = k + 1;
            }
            else    // total < target，不能让n台电脑同时运行k分钟
            {
                right = k;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}