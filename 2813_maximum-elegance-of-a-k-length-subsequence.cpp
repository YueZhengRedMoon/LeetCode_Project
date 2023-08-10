#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include "debug.h"

class Solution
{
public:
    long long findMaximumElegance(std::vector<std::vector<int>> &items, int k)
    {
        int n = items.size();
        long long sum = 0, elegance, distinct, ans;
        std::unordered_map<int, int> category;


        std::sort(items.begin(), items.end(), std::greater<std::vector<int>>());
        for (int i = 0; i < k; ++i)
        {
            ++category[items[i][1]];
            sum += items[i][0];
        }
        distinct = category.size();
        ans = sum + distinct * distinct;

        debug::printVector2D(items, ',', ' ');
        std::cout << "\nsum = " << sum << ", distinct = " << distinct << ", elegance = " << ans << std::endl;

        for (int i = k, j = k - 1; i < n && j >= 0; ++i)
        {
            if (category.find(items[i][1]) != category.end())
                continue;

            while (j >= 0 && category[items[j][1]] == 1)
                --j;

            if (j >= 0)
            {
                --category[items[j][1]];
                category[items[i][1]] = 1;
                sum = sum - items[j][0] + items[i][0];
                --j;
                ++distinct;
                elegance = sum + distinct * distinct;
                if (elegance > ans)
                    ans = elegance;

                std::cout << "sum = " << sum << ", distinct = " << distinct << ", elegance = " << elegance << std::endl;
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> items = {{1,5},{4,5},{9,8},{6,8},{4,7},{4,2},{4,3},{10,8}};
    int k = 4;
    long long ans = solution.findMaximumElegance(items, k);
    logObj(ans);
    return 0;
}
