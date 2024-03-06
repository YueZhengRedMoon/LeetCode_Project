#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> divisibilityArray(std::string word, int m)
    {
        int n = word.size();
        std::vector<int> ans(n);
        long long x = 0;
        for (int i = 0; i < n; ++i)
        {
            x = (x * 10 + word[i] - '0') % m;
            ans[i] = (x == 0);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
