#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int largestValsFromLabels(std::vector<int> &values, std::vector<int> &labels, int numWanted, int useLimit)
    {
        int n = values.size();
        std::vector<std::pair<int, int>> pairs(n);
        std::unordered_map<int, int> useCount;
        for (int i = 0; i < n; ++i)
        {
            pairs[i].first = values[i];
            pairs[i].second = labels[i];
        }
        std::sort(pairs.begin(), pairs.end());

        int ans = 0;
        int num = 0;
        for (int i = n - 1; i >= 0 && num < numWanted; --i)
        {
            if (useCount[pairs[i].second] >= useLimit) continue;

            ans += pairs[i].first;
            ++useCount[pairs[i].second];
            ++num;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}