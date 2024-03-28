#include <iostream>
#include <vector>

class Solution
{
public:
    int firstDayBeenInAllRooms(std::vector<int>& nextVisit)
    {
        // f[i]:从奇数次访问i号房间到奇数次访问j号房间需要的天数
        // f[i] = 2 + f[j] + f[j+1] + ... + f[i-1]，其中2为两次访问i号房间的天数，j=nextVisit[i]
        // 前缀和: s[0] = 0, s[i+1] = f[0] + f[1] + ... + f[i]
        // f[i] = 2 + s[i] - s[j]
        // 根据前缀和定义有：s[i+1] = s[i] + f[i] = s[i] + 2 + s[i] - s[j] = 2 * s[i] - s[j] + 2
        // ans = s[n - 1] + 1

        const int MOD = 1'000'000'007;
        int n = nextVisit.size();
        std::vector<long long> s(n);
        for (int i = 0; i < n - 1; ++i)
        {
            int j = nextVisit[i];
            s[i + 1] = ((2 * s[i] + 2) % MOD + MOD - s[j]) % MOD;
        }
        return s[n - 1];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
