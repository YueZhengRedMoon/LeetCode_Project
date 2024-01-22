#include <iostream>
#include <algorithm>

class Solution
{
public:
    int maximumSwap(int num)
    {
        std::string s1 = std::to_string(num);
        std::string s2(s1);
        std::sort(s2.begin(), s2.end(), std::greater<>());
        int n = s1.size();
        for (int i = 0; i < n; ++i)
        {
            if (s1[i] != s2[i])
            {
                for (int j = n - 1; j > i; --j)
                {
                    if (s1[j] == s2[i])
                    {
                        std::swap(s1[i], s1[j]);
                        break;
                    }
                }
                break;
            }
        }
        return std::stoi(s1);
    }
};

class Solution2
{
public:
    int maximumSwap(int num)
    {
        std::string s = std::to_string(num);
        int n = s.size();
        int maxIdx = n - 1, p = - 1, q = 0;
        for (int i = n - 2; i >= 0; --i)
        {
            if (s[i] > s[maxIdx])
            {
                maxIdx = i;
            }
            else if (s[i] < s[maxIdx])
            {
                p = i;
                q = maxIdx;
            }
        }
        if (p == -1)
        {
            return num;
        }
        std::swap(s[p], s[q]);
        return std::stoi(s);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
