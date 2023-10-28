#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> &flowers, std::vector<int> &people)
    {
        int n = people.size();
        std::vector<int> ans(n, 0);
        std::vector<std::vector<int>> flowers2(flowers);

        // 按照start升序排序
        std::sort(flowers.begin(), flowers.end());
        // 按照end升序排序
        std::sort(flowers2.begin(), flowers2.end(), [](const std::vector<int> &lhs, const std::vector<int> &rhs){
            return lhs[1] < rhs[1];
        });

        for (int i = 0; i < n; ++i)
        {
            int bloomCount = upperBound(flowers, people[i]);    // 第i个人到达时已经开的花的数量
            if (bloomCount)
            {
                int witheredCount = lowerBound(flowers2, people[i]);    // 第i个人到达时已经凋谢的花的数量
                ans[i] = bloomCount - witheredCount;
            }
        }

        return ans;
    }

private:
    // 找到开花时间>t的第一朵花
    int upperBound(const std::vector<std::vector<int>> &flowers, int t)
    {
        int left = 0, right = flowers.size();
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (flowers[mid][0] > t)
                right = mid;
            else    // flowers[mid][0] <= startTime
                left = mid + 1;
        }
        return left;
    }

    // 找到花谢时间>=t的第一朵花
    int lowerBound(const std::vector<std::vector<int>> &flowers, int t)
    {
        int left = 0, right = flowers.size();
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (flowers[mid][1] >= t)
            {
                right = mid;
            }
            else    // flowers[mid][1] < t
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

class Solution2
{
public:
    std::vector<int> fullBloomFlowers(std::vector<std::vector<int>> &flowers, std::vector<int> &people)
    {
        std::map<int, int> diff;
        for (const std::vector<int> &f : flowers)
        {
            ++diff[f[0]];
            --diff[f[1] + 1];
        }

        int n = people.size();
        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(), [&](int lhs, int rhs) { return people[lhs] < people[rhs]; });

        auto it = diff.begin();
        int sum = 0;
        for (int i : id)
        {
            while (it != diff.end() && it->first <= people[i])
                sum += it++->second;
            people[i] = sum;
        }

        return people;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> flowers = {{1,6},{3,7},{9,12},{4,13}};
    std::vector<int> people = {2,3,7,11};
    std::vector<int> ans = solution.fullBloomFlowers(flowers, people);
    debug::printVector(ans);
    return 0;
}
