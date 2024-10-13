#include <iostream>
#include <cmath>

class Solution
{
public:
    // 假设需要扔x次鸡蛋来确定f的楼层，则x为最小的满足(1+x)*x/2 >= n的正整数
    // 1.先在x层扔鸡蛋，如果鸡蛋碎了，则依次在1,2,3...,x-1层扔鸡蛋，最多总共扔1+x-1=x次
    // 2.如果在x层扔鸡蛋碎了，则接下来在x+x-1层鸡蛋，如果鸡蛋在x+x-1层碎了，则依次在x+1,x+2,...,x+x-2层，最多总共扔1+1+x-2=x层
    // 3.如果在x+x-1层扔鸡蛋没碎，则接下来在x+x-1+x-2层扔鸡蛋...
    // 依次类推，每次鸡蛋没碎时，递减的在更高的楼层扔鸡蛋，最小的满足x+(x-1)+(x-2)+...+1>=n的正整数x即为答案

    int twoEggDrop(int n)
    {
        return (int) std::ceil((std::sqrt(1 + 8 * n) - 1.0) / 2.0);
    }
};

int memo[1001];

class Solution2
{
public:
    // 定义状态dfs(i)表示在一栋有i层楼的建筑中扔鸡蛋，无论f等于多少，都能确定f的最小操作次数
    // 枚举第一枚鸡蛋在j=1,2,3...,i楼扔下:
    //  - 如果鸡蛋碎了，接下来依次在1,2,3..,j-1楼中扔第二枚鸡蛋，最多要操作1+(j-1)=j次
    //  - 如果鸡蛋没碎，接下来在j+1楼到i楼中继续扔第一枚鸡蛋，这等价于在一栋有i-j层楼的建筑中扔鸡蛋的子问题，即dfs(i-j)，将其加1即为总操作次数
    //  - 以上两种情况取最大值，即为在第j楼扔下第一枚鸡蛋，到最终确定f，所需的操作次数

    int twoEggDrop(int n)
    {
        if (n == 0)
            return 0;

        int& res = memo[n];
        if (res)
            return res;

        res = INT_MAX;
        for (int j = 1; j <= n; ++j)
        {
            res = std::min(res, std::max(j, twoEggDrop(n - j) + 1));
        }
        return res;
    }
};

const int MAX_N = 1001;
int f[MAX_N];
int init = [](){
    for (int i = 1; i < MAX_N; ++i)
    {
        f[i] = INT_MAX;
        for (int j = 1; j <= i; ++j)
        {
            f[i] = std::min(f[i], std::max(f[j], f[i - j] + 1));
        }
    }
    return 0;
}();

class Solution3
{
public:
    int twoEggDrop(int n)
    {
        return f[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
