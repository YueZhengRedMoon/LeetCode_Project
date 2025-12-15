#include <iostream>
#include <vector>

class Solution
{
public:
    long long getDescentPeriods(std::vector<int>& prices)
    {
        long long ans = 0;
        int n = prices.size();
        int cnt = 0;    // 连续下降的天数
        int prePrice = prices[0] + 1;   // 前一天的股价
        for (int i = 0; i < n; ++i)
        {
            if (prePrice - prices[i] == 1)
            {
                ++cnt;
            }
            else
            {
                cnt = 1;
            }
            ans += cnt;
            prePrice = prices[i];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}