#include <iostream>
#include <vector>

class Solution
{
public:
    int findPermutationDifference(std::string s, std::string t)
    {
        int posS[26]{0};
        int posT[26]{0};
        int n = s.size(), ans = 0;
        for (int i = 0; i < n; ++i)
        {
            posS[s[i] - 'a'] = i;
            posT[t[i] - 'a'] = i;
        }
        for (int i = 0; i < 26; ++i)
        {
            ans += std::abs(posS[i] - posT[i]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
