#include <iostream>
#include <string>

class Solution
{
public:
    int numberOfSubstrings(std::string s)
    {
        int n = s.size(), ans = 0, cntA = 0, cntB = 0, cntC = 0;
        for (int l = 0, r = 0; r < n; ++r)
        {
            updateCnt(s[r], cntA, cntB, cntC, 1);
            while (cntA > 0 && cntB > 0 && cntC > 0)
            {
                updateCnt(s[l++], cntA, cntB, cntC, -1);
            }
            // 区间(l, r]中没有都有abc
            // 区间[0, r], [1, r], ..., [l-1, r]共l个区间里都有abc
            ans += l;
        }
        return ans;
    }

private:
    void updateCnt(char ch, int& cntA, int& cntB, int& cntC, int delta)
    {
        switch (ch)
        {
            case 'a':
                cntA += delta;
                break;
            case 'b':
                cntB += delta;
                break;
            case 'c':
                cntC += delta;
                break;
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}