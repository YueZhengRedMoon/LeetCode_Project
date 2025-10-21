#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

class Solution
{
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations)
    {
        std::unordered_map<int, int> cnt;
        std::map<int, int> diff;
        for (int x : nums)
        {
            ++cnt[x];
            diff[x]; // 把 x 插入 diff，以保证下面能遍历到 x

            // 差分数组操作，等价于将[x-k, x+k]中的所有数的出现次数+1
            ++diff[x - k];
            --diff[x + k + 1];
        }

        int ans = 0, sumD = 0;
        for (auto& [x, d] : diff)   // 遍历每个数的出现次数
        {
            // 累加差分数组，等价于求目前所有数的出现次数
            sumD += d;

            // 设有sumD个数可以变成x
            // 如果x不在nums中，那么x的最大出现次数不能超过numOperations，与sumD取最小值，得min(sumD,numOperations)
            // 如果x在nums中，且出现了cnt[x]次，那么有sumD−cnt[x]个其他元素（不等于x的数）可以变成x，但这不能超过numOperations，
            // 所以有min(sumD−cnt[x],numOperations)个其他元素可以变成x，再加上x自身出现的次数cnt[x]，得到x的最大频率为
            // cnt[x]+min(sumD−cnt[x],numOperations)=min(sumD,cnt[x]+numOperations)
            // 上式兼容x不在nums中的情况，此时 cnt[x]=0
            ans = std::max(ans, std::min(sumD, cnt[x] + numOperations));
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}