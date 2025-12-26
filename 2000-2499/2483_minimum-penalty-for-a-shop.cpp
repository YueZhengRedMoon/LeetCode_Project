#include <iostream>
#include <algorithm>

class Solution
{
public:
    int bestClosingTime(std::string customers)
    {
        int cntY = std::count_if(customers.begin(), customers.end(), [](char c) -> bool {return c == 'Y';});
        int cntN = 0;
        int n = customers.size();
        int ans = n, minCost = n;
        for (int i = 0; i <= n; ++i)
        {
            int cost = cntN + cntY;
            if (cost < minCost)
            {
                minCost = cost;
                ans = i;
            }

            if (i < n)
            {
                if (customers[i] == 'N')
                    ++cntN;
                else
                    --cntY;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int bestClosingTime(std::string customers)
    {
        int penalty = 0, minPenalty = 0, ans = 0;
        for (int i = 0; i < customers.size(); ++i)  // 枚举关门时刻i+1
        {
            penalty += customers[i] == 'N' ? 1 : -1;
            if (penalty < minPenalty)
            {
                minPenalty = penalty;
                ans = i + 1;
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