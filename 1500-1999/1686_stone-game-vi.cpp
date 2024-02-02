#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int stoneGameVI(std::vector<int> &a, std::vector<int> &b)
    {
        int n = a.size();
        std::vector<int> c(n);
        std::iota(c.begin(), c.end(), 0);
        std::sort(c.begin(), c.end(), [&](int i, int j) {return a[i] + b[i] > a[j] + b[j];});
        int diff = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i % 2 == 0)
                diff += a[c[i]];
            else
                diff -= b[c[i]];
        }
        if (diff > 0)
            return 1;
        else if (diff < 0)
            return -1;
        else
            return 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
