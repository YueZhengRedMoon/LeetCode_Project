#include <iostream>
#include <vector>

class Solution
{
public:
    int punishmentNumber(int n)
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (backtracking(i * i, i))
            {
                ans += i * i;
            }
        }
        return ans;
    }

    bool backtracking(int num, int target)
    {
        if (num == target)
        {
            return true;
        }
        int temp = num;
        int delta = 0;
        int i = 0;
        int j = 1;
        while (temp > 0)
        {
            delta += (temp % 10) * j;
            if (delta > target)
            {
                break;
            }
            ++i;
            j *= 10;
            if (backtracking((num - delta) / j, target - delta))
            {
                return true;
            }
            temp /= 10;
        }
        return false;
    }
};

int main()
{
    Solution solution;
    int ans = solution.punishmentNumber(37);
    std::cout << ans << std::endl;
    return 0;
}
