#include <iostream>
#include <vector>

class Solution
{
public:
    int minChanges(std::string s)
    {
        int oneCnt = 0, zeroCnt = 0, ans = 0, n = s.size();
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '0')
                ++zeroCnt;
            else
                ++oneCnt;

            if (i % 2 == 1)
            {
                if (oneCnt && zeroCnt)
                {
                    ans += std::min(oneCnt, zeroCnt);
                }
                oneCnt = 0;
                zeroCnt = 0;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int minChanges(std::string s)
    {
        int ans = 0, n = s.size();
        for (int i = 0; i < n; i += 2)
        {
            ans += (s[i] != s[i + 1]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
