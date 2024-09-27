#include <iostream>
#include <vector>

class Solution
{
public:
    int takeCharacters(std::string s, int k)
    {
        int n = s.size(), totalA = 0, totalB = 0, totalC = 0;
        for (char c : s)
        {
            updateCount(c, totalA, totalB, totalC, 1);
        }

        if (totalA < k || totalB < k || totalC < k)
            return -1;

        // 滑动窗口s[left, right]中是拿走两边的字符后剩下的字符
        int maxWindowLen = 0, maxA = totalA - k, maxB = totalB - k, maxC = totalC - k;
        int cntA = 0, cntB = 0, cntC = 0;
        int left = 0, right = 0;
        std::cout << "maxA = " << maxA << ", maxB = " << maxB << ", maxC = " << maxC << std::endl;
        while (right < n)
        {
            while (right < n && cntA <= maxA && cntB <= maxB && cntC <= maxC)
            {
                updateCount(s[right++], cntA, cntB, cntC, 1);
            }
            maxWindowLen = std::max(maxWindowLen, right - left - (cntA > maxA || cntB > maxB || cntC > maxC));

            std::cout << "left = " << left << ", right = " << right << ":";
            for (int i = 0; i <= n; ++i)
            {
                if (i == left || i == right)
                    std::cout << '|';
                if (i < n)
                    std::cout << s[i];
            }
            std::cout << std::endl;

            while (left < right && (cntA > maxA || cntB > maxB || cntC > maxC))
            {
                updateCount(s[left++], cntA, cntB, cntC, -1);
            }
        }

        return n - maxWindowLen;
    }

private:
    void updateCount(char c, int& cntA, int& cntB, int& cntC, int delta)
    {
        if (c == 'a')
            cntA += delta;
        else if (c == 'b')
            cntB += delta;
        else
            cntC += delta;
    }
};

int main()
{
    Solution solution;
    std::string s = "aabaaaacaabc";
    int k = 0;
    int ans = solution.takeCharacters(s, k);
    std::cout << ans << std::endl;
    return 0;
}
