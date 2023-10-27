#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    /**
     * 1.对于同一个比特位，由于AND和OR不会改变都为0和都为1的情况，所以操作等价于：
     *   把一个数的0和另一个数的同一个比特位上的1交换。
     * 2.设交换前两个数是x和y，且x>y。把小的数上的1给大的数，假设交换后x增加了d，那么y也减小了d。
     *   交换前：x^2 + y^2。
     *   交换后：(x+d)^2 + (y-d)^2 = x^2 + y^2 + 2d(x-y) + 2d^2 > x^2 + y^2
     *   说明应该通过交换，让一个数越大越好，这相当于把1都聚集到一个数中，比分散到不同的数更好。
     * 3.由于可以操作任意次，一定可以“组装“出尽量大的数：
     *      i.对于每个比特位，统计nums在比特位上有多少1，记到一个cnt数组中
     *      ii.循环k次，每次循环，”组装“一个数（记为x）
     *      iii.遍历cnt数组，只要cnt[i]>0，就将其减一，并将2^i加到x中。这样相当于把1尽量聚集在一个数中
     *      iv.把x^2加入到答案中
     * */

    int maxSum(std::vector<int> &nums, int k)
    {
        long long ans = 0;
        int cnt[30]{};
        for (int num : nums)
        {
            for (int i = 0; i < 30; ++i)
            {
                cnt[i] += (num >> i) & 1;
            }
        }
        const long long MOD = 1e9 + 7;
        while (k--)
        {
            int x = 0;
            for (int i = 0; i < 30; ++i)
            {
                if (cnt[i] > 0)
                {
                    --cnt[i];
                    x |= (1 << i);
                }
            }
            ans = (ans + (long long) x * x % MOD) % MOD;
        }
        return (int) ans;
    }
};

int main()
{
    Solution solution;
    return 0;
}
