#include <iostream>
#include <algorithm>
#include <vector>

const int MAX_NUM = 100001;
int divisorNum[MAX_NUM];
int divisorSum[MAX_NUM];

int init = []() -> int {
    for (int i = 1; i < MAX_NUM; ++i)
    {
        for (int j = i; j < MAX_NUM; j += i)    // 枚举i的倍数j
        {
            // i是j的因子
            ++divisorNum[j];
            divisorSum[j] += i;
        }
    }
    return 0;
}();

class Solution
{
public:
    int sumFourDivisors(std::vector<int>& nums)
    {
        int ans = 0;
        for (int x : nums)
        {
            if (divisorNum[x] == 4)
            {
                ans += divisorSum[x];
            }
        }
        return ans;
    }
};


namespace MySolution
{
    const int MAX_NUM = 100001;
    bool isPrime[MAX_NUM];
    int fourDivisors[MAX_NUM];  // fourDivisors[x]:若x恰有4个因数，则存储其各因数之和; =0, x不恰有4个因数; =-1,不确定
    int init = []() -> int {
        std::fill(std::begin(isPrime) + 2, std::end(isPrime), true);
        std::fill(std::begin(fourDivisors) + 6, std::end(fourDivisors), -1);
        for (int i = 2; i < MAX_NUM; ++i)
        {
            if (isPrime[i])
            {
                for (int j = i + i; j < MAX_NUM; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }
        return 0;
    }();

    class Solution
    {
    public:
        int sumFourDivisors(std::vector<int>& nums)
        {
            int ans = 0;
            for (int x : nums)
            {
                if (x <= 5 || isPrime[x])
                    continue;

                if (fourDivisors[x] == -1)
                {
                    fourDivisors[x] = calc(x);
                }
                ans += fourDivisors[x];
            }
            return ans;
        }

    private:
        // 计算并返回x的四因数之和（如果x恰有4个因数），如果x不恰有4个因数，则返回0
        int calc(int x)
        {
            int cnt = 1, res = 1;
            for (int i = 2; i <= x && cnt <= 4; ++i)
            {
                if (x % i == 0)
                {
                    ++cnt;
                    res += i;
                }
            }
            return cnt == 4 ? res : 0;
        }
    };
}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}