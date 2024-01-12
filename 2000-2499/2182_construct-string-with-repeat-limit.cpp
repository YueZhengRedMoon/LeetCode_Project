#include <iostream>
#include "debug.h"

class Solution
{
public:
    std::string repeatLimitedString(std::string s, int repeatLimit)
    {
        int counter[26]{};
        for (char c : s)
            ++counter[c - 'a'];
        std::string ans;
        int i = 25;
        while (i >= 0)
        {
            if (counter[i] == 0)
            {
                --i;
                continue;
            }
            while (counter[i])
            {
                if (counter[i] > repeatLimit)
                {
                    ans.append(repeatLimit, 'a' + i);
                    counter[i] -= repeatLimit;
                    int j;
                    for (j = i - 1; j >= 0 && counter[j] == 0; --j);
                    if (j >= 0)
                    {
                        ans.push_back('a' + j);
                        --counter[j];
                    }
                    else
                    {
                        i = 0;
                        break;
                    }
                }
                else
                {
                    ans.append(counter[i], 'a' + i);
                    counter[i] = 0;
                }
            }
            --i;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::string s = "cczazcc";
    int repeatLimit = 3;
    std::string ans = solution.repeatLimitedString(s, repeatLimit);
    logObj(ans);
    return 0;
}
