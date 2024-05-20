#include <iostream>
#include <vector>

class Solution
{
public:
    int reverse(int x)
    {
        int ans = 0, flag;
        if (x > 0)
            flag = 1;
        else if (x < 0)
            flag = -1;
        else
            return 0;

        int tmp = std::abs(x);
        while (tmp)
        {
            int d = tmp % 10;
            if (flag > 0)
            {
                // ans * 10 + d <= INT_MAX
                if (INT_MAX / 10 >= ans && INT_MAX - ans * 10 >= d)
                    ans = ans * 10 + d;
                else
                    return 0;
            }
            else
            {
                // ans * 10 - d >= INT_MIN
                if (INT_MIN / 10 <= ans && (ans == 0 || ans * 10 - INT_MIN >= d))
                    ans = ans * 10 - d;
                else
                    return 0;
            }
            tmp /= 10;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
