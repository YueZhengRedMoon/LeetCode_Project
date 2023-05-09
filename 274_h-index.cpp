#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int hIndex(std::vector<int> &citations)
    {
        std::sort(citations.begin(), citations.end());

        int n = citations.size();
        if (citations[0] >= n)
        {
            return n;
        }
        for (int h = n - 1; h >= 1; --h)
        {
            if (citations[n - h - 1] <= h && citations[n - h] >= h)
            {
                return h;
            }
        }
        return citations[0] ? 1 : 0;
    }
};

class Solution2
{
public:
    int hIndex(std::vector<int> &citations)
    {
        int n = citations.size(), tot = 0;
        std::vector<int> counter(n + 1);
        for (int citation : citations)
        {
            if (citation >= n)
            {
                ++counter[n];
            }
            else
            {
                ++counter[citation];
            }
        }

        for (int i = n; i >= 0; --i)
        {
            tot += counter[i];
            if (tot >= i)
            {
                return i;
            }
        }

        return 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
