#include <iostream>
#include <vector>

class Solution
{
public:
    long long distributeCandies(int n, int limit)
    {
        long long ans = 0;
        for (long long i = 0LL; i <= std::min(limit, n); ++i)
            ans += distributeCandies2(n - i, limit);
        return ans;
    }

private:
    // 将n个糖果分给2个小朋友，每个小朋友糖果数不超过limit个糖果的方案数
    long long distributeCandies2(int n, int limit)
    {
        // 当n<=limit时，有(0,n), (1, n-1), ..., (n, 0)共n+1种分法
        if (n <= limit)
            return n + 1LL;
        // 当n>limit，且n-limit<=limit时，有(limit, n-limit), (limit-1, n-limit+1), ..., (n-limit, limit)共2 * limit - n + 1种分法
        if (n <= 2 * limit)
            return 2LL * limit - n + 1LL;
        // 当n>2*limit时，不存在有效的分法
        return 0LL;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
