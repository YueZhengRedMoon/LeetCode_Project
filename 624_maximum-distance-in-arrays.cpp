#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxDistance(std::vector<std::vector<int>> &arrays)
    {
        int n = arrays.size();
        std::vector<int> leftMin(n), leftMax(n), rightMin(n), rightMax(n);

        leftMin[0] = arrays[0].front();
        leftMax[0] = arrays[0].back();
        for (int i = 1; i < n; ++i)
        {
            leftMin[i] = std::min(leftMin[i - 1], arrays[i].front());
            leftMax[i] = std::max(leftMax[i - 1], arrays[i].back());
        }

        rightMin[n - 1] = arrays[n - 1].front();
        rightMax[n - 1] = arrays[n - 1].back();
        for (int i = n - 2; i >= 0; --i)
        {
            rightMin[i] = std::min(rightMin[i + 1], arrays[i].front());
            rightMax[i] = std::max(rightMax[i + 1], arrays[i].back());
        }

        int ans = std::max(std::abs(rightMax[1] - arrays[0].front()), std::abs(arrays[0].back() - rightMin[1]));
        for (int i = 1; i < n - 1; ++i)
        {
            ans = std::max({ans,
                              std::abs(std::max(leftMax[i - 1], rightMax[i + 1]) - arrays[i].front()),
                              std::abs(arrays[i].back() - std::min(leftMin[i - 1], rightMin[i + 1]))});
        }
        ans = std::max({ans,
                        std::abs(leftMax[n - 2] - arrays[n - 1].front()),
                        std::abs(arrays[n - 1].back() - leftMin[n - 2])});

        return ans;
    }
};

class Solution2
{
public:
    int maxDistance(std::vector<std::vector<int>> &arrays)
    {
        int ans = 0, minVal = arrays[0].front(), maxVal = arrays[0].back();
        for (int i = 1; i < arrays.size(); ++i)
        {
            ans = std::max({ans, std::abs(arrays[i].back() - minVal), std::abs(maxVal - arrays[i].front())});
            minVal = std::min(minVal, arrays[i].front());
            maxVal = std::max(maxVal, arrays[i].back());
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> arrays = {{1, 2, 3}, {4, 5}, {1, 2, 3}};
    int ans = solution.maxDistance(arrays);
    std::cout << ans << std::endl;
    return 0;
}