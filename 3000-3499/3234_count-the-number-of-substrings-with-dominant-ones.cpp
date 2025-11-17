#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfSubstrings(std::string s)
    {
        std::vector<int> pos0 = {-1};   // 所有0的下标，加个-1哨兵，方便处理cnt0达到最大时的计数
        int total1 = 0;  // [0, r]中的1的个数
        int ans = 0;
        for (int r = 0; r < s.size(); ++r)
        {
            if (s[r] == '0')
            {
                pos0.push_back(r);  // 记录0的下标
            }
            else    // s[r] == '1'
            {
                ++total1;
                ans += r - pos0.back();     // 单独计算不含0的子串个数
            }

            int m = pos0.size();
            for (int i = m - 1; i > 0 && (m - i) * (m - i) <= total1; --i)  // 倒着遍历pos0，枚举恰有cnt0个0的情况
            {
                int p = pos0[i - 1], q = pos0[i];   // p:上上个0的位置, q:上个0的位置
                int cnt0 = m - i;
                int cnt1 = r - q + 1 - cnt0;    // [q, r]中1的个数 = [q, r]的长度-cnt0
                ans += std::max(q - std::max(cnt0 * cnt0 - cnt1, 0) - p, 0);
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