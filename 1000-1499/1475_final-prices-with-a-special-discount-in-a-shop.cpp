#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> finalPrices(std::vector<int> &prices)
    {
        int n = prices.size();
        std::stack<int> stack;
        for (int i = 0; i < n; ++i)
        {
            while (!stack.empty() && prices[stack.top()] >= prices[i])
            {
                prices[stack.top()] -= prices[i];
                stack.pop();
            }
            stack.push(i);
        }
        return prices;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
