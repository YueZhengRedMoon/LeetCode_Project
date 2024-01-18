#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    long long minimumRemoval(std::vector<int> &beans)
    {
        long long sum = std::accumulate(beans.begin(), beans.end(), 0ll);
        long long ans = sum;
        int n = beans.size();
        std::sort(beans.begin(), beans.end(), std::greater<>());
        for (int i = 0; i < n; ++i)
        {
            ans = std::min(ans, sum - (i + 1ll) * beans[i]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
