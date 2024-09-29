#include <iostream>
#include <vector>

class Solution
{
public:
    int timeRequiredToBuy(std::vector<int>& tickets, int k)
    {
        int ans = 0;
        for (int i = 0; i <= k; ++i)
            ans += std::min(tickets[i], tickets[k]);
        for (int i = k + 1; i < tickets.size(); ++i)
            ans += std::min(tickets[i], tickets[k] - 1);
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
