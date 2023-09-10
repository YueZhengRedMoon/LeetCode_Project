#include <iostream>
#include <vector>
#include <cstring>

class Solution
{
public:
    int countSymmetricIntegers(int low, int high)
    {
        int ans = 0;
        for (int i = low; i <= high; ++i)
        {
            std::string s = std::to_string(i);
            int len = s.size();
            if (len % 2 != 0)
                continue;

            int leftSum = 0, rightSum = 0, n = len / 2;
            for (int j = 0; j < n; ++j)
                leftSum += s[j] - '0';
            for (int j = n; j < len; ++j)
                rightSum += s[j] - '0';

            ans += (leftSum == rightSum);
        }
        return ans;
    }
};

class Solution2
{
public:
    int countSymmetricIntegers(int low, int high)
    {
        std::memset(memo, -1, sizeof(memo));
        return calc(high) - calc(low - 1);
    }

private:
    int digits[5]{};
    int memo[5][19]{};

    int calc(int num)
    {
        if (num == 0)
            return 0;

        int i = 0;
        while (num > 0)
        {
            digits[i++] = num % 10;
            num /= 10;
        }

        return f(i - 1, 0, 0, true, false);
    }

    int f(int i, int len, int sum, bool isLimit, bool isNum)
    {
        if (i == -1)
        {
            return (len & 1) == 0 && sum == 0 && isNum;
        }

        if (isNum &&  ((len + i) & 1) == 0)
            return 0;

        if (isNum && !isLimit && memo[i][sum] != -1)
            return memo[i][sum];

        int res = 0;
        int up = isLimit ? digits[i] : 9;
        for (int d = 0; d <= up; ++d)
        {
            int newLen = !isNum && d == 0 ? 0 : len + 1;
            int newSum = len < i ? sum + d : sum - d;
            if (newSum < 0)
                break;
            res += f(i - 1, newLen, newSum, isLimit && d == up, isNum || d != 0);
        }

        if (isNum && !isLimit)
            memo[i][sum] = res;

        return res;
    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
