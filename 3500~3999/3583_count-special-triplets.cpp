#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int specialTriplets(std::vector<int>& nums)
    {
        std::unordered_map<int, int> leftCnt, rightCnt;
        for (int x : nums)
        {
            ++rightCnt[x];
        }

        long long ans = 0;
        constexpr int MOD = 1'000'000'007;
        for (int x : nums)
        {
            --rightCnt[x];
            long long y = x + x;
            ans = (ans + (long long) leftCnt[y] * rightCnt[y]) % MOD;
            ++leftCnt[x];
        }
        return (int) ans;
    }
};

class Solution2
{
public:
    int specialTriplets(std::vector<int>& nums)
    {
        constexpr int MOD = 1'000'000'007;
        std::unordered_map<int, int> cnt1;
        std::unordered_map<int, long long> cnt12;   // 有多少个二元组(i,j)满足i<j<k且nums[i]=x且nums[j]=x/2, key:x=nums[k]
        long long cnt123 = 0;
        for (int x : nums)
        {
            if (x % 2 == 0)
            {
                cnt123 += cnt12[x / 2]; // 把x当作nums[k]
            }
            cnt12[x] += cnt1[x * 2];    // 把x当作nums[j]
            ++cnt1[x];  // 把x当作nums[i]
        }
        return cnt123 % MOD;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}