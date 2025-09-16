#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    std::vector<int> replaceNonCoprimes(std::vector<int>& nums)
    {
        std::vector<int> ans;
        for (int x : nums)
        {
            while (!ans.empty() && std::gcd(ans.back(), x) > 1)
            {
                x = std::lcm(ans.back(), x);
                ans.pop_back();
            }
            ans.push_back(x);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
