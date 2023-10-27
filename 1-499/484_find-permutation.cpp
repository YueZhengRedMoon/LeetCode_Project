#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

/** 错误 */
class Solution
{
public:
    std::vector<int> findPermutation(std::string s)
    {
        int n = s.size() + 1;
        std::vector<int> ans(n);

        ans[0] = 1;
        int minVal = 1, count = 1;
        if (s[0] == 'I')
        {
            ans[1] = 2;
        }
        else
        {
            ans[1] = 0;
            minVal = 0;
        }

        for (int i = 1; i < n - 1; ++i)
        {
            if (s[i] == 'I')
            {
                if (s[i - 1] == 'I')
                {
                    ans[i + 1] = ans[i] + 1;
                    ++count;
                }
                else
                {
                    ans[i + 1] = ans[i - count] + 1;
                    count = 1;
                }
            }
            else
            {
                if (s[i - 1] == 'D')
                {
                    ans[i + 1] = ans[i] - 1;
                    ++count;
                }
                else
                {
                    ans[i + 1] = ans[i - count] - 1;
                    count = 1;
                }
                if (ans[i + 1] < minVal)
                {
                    minVal = ans[i + 1];
                }
            }
        }

        int delta = 1 - minVal;
        if (delta > 0)
        {
            for (int &val : ans)
            {
                val += delta;
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> findPermutation(std::string s)
    {
        int len = s.size();
        int n = len + 1;
        std::vector<int> ans(n);
        std::iota(ans.begin(), ans.end(), 1);

        int i = 1;
        while (i <= len)
        {
            int j = i;
            while (i <= len && s[i - 1] == 'D')
            {
                ++i;
            }
            if (j != i)
            {
                std::reverse(ans.begin() + j - 1, ans.begin() + i);
            }
            ++i;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
