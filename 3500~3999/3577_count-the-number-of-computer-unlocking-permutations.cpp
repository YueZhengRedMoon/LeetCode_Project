#include <iostream>
#include <vector>

class Solution
{
public:
    int countPermutations(std::vector<int>& complexity)
    {
        constexpr int MOD = 1'000'000'007;
        long long ans = 1;
        for (int i = 1; i < complexity.size(); ++i)
        {
            if (complexity[0] >= complexity[i])
                return 0;
            ans = (ans * i) % MOD;
        }
        return (int) ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}