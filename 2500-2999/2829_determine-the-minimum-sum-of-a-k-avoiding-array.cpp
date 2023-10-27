#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumSum(int n, int k)
    {
        std::vector<bool> contain(k + 1, true);
        int ans = 0, count = 0;
        for (int i = 1; i <= k && count < n; ++i)
        {
            if (contain[i])
            {
                ans += i;
                contain[k - i] = false;
                ++count;
            }
        }
        if (count < n)
        {
            count = n - count;
            ans += (k + 1 + k + count) * count / 2;
        }
        return ans;
    }
};

class Solution2
{
public:
    int minimumSum(int n, int k)
    {
        int m = std::min(n, k / 2);
        return ((1 + m) * m + (k + k + n - m - 1) * (n - m)) / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
