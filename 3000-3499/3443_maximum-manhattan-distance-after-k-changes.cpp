#include <iostream>
#include <string>
#include <algorithm>

class Solution
{
public:
    int maxDistance(std::string s, int k)
    {
        int cntN = 0, cntS = 0, cntE = 0, cntW = 0, ans = 0, left = 0;
        auto f = [&](int a, int b) -> int {
            int d = std::min({a, b, left});
            left -= d;
            return std::abs(a - b) + d * 2;
        };
        for (char c : s)
        {
            switch (c)
            {
                case 'N':
                    ++cntN;
                    break;
                case 'S':
                    ++cntS;
                    break;
                case 'E':
                    ++cntE;
                    break;
                case 'W':
                    ++cntW;
                    break;
            }

            left = k;
            ans = std::max(ans, f(cntN, cntS) + f(cntE, cntW));
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
