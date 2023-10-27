#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxArea(int h, int w, std::vector<int> &horizontalCuts, std::vector<int> &verticalCuts)
    {
        std::sort(horizontalCuts.begin(), horizontalCuts.end());
        std::sort(verticalCuts.begin(), verticalCuts.end());

        int maxDh = std::max(horizontalCuts[0], h - horizontalCuts.back());
        for (int i = 1; i < horizontalCuts.size(); ++i)
            maxDh = std::max(maxDh, horizontalCuts[i] - horizontalCuts[i - 1]);

        int maxDv = std::max(verticalCuts[0], w - verticalCuts.back());
        for (int i = 1; i < verticalCuts.size(); ++i)
            maxDv = std::max(maxDv, verticalCuts[i] - verticalCuts[i - 1]);

        return (int) ((long long) maxDh * maxDv % 1000000007ll);
    }
};

int main()
{
    Solution solution;
    int h = 5, w = 4;
    std::vector<int> horizontalCuts = {1, 2, 4}, verticalCuts = {1, 3};
    int ans = solution.maxArea(h, w, horizontalCuts, verticalCuts);
    std::cout << ans << std::endl;
    return 0;
}