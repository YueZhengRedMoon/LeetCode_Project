#include <iostream>
#include <vector>

class Solution
{
public:
    std::string convert(std::string s, int numRows)
    {
        if (numRows == 1)
        {
            return s;
        }

        int n = s.size();
        std::string ans(n, ' ');
        int index = 0;
        int delta = numRows + numRows - 2;
        for (int i = 0; i < numRows; ++i)
        {
            if (i == 0 || i == numRows - 1)
            {
                for (int j = i; j < n; j += delta)
                {
                    ans[index++] = s[j];
                }
            }
            else
            {
                for (int j = i, k = delta - i; j < n; j += delta, k += delta)
                {
                    ans[index++] = s[j];
                    if (k < n) ans[index++] = s[k];
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::string s = "PAYPALISHIRING";
    int numRows = 4;
    Solution solution;
    std::string result = solution.convert(s, numRows);
    std::cout << result << std::endl;

    int numRows2 = 3;
    std::string result2 = solution.convert(s, numRows2);
    std::cout << result2 << std::endl;
    return 0;
}
