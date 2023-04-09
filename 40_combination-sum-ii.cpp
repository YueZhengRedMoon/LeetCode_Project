#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target)
    {
        std::vector<bool> used(candidates.size(), false);
        std::sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, used);
        return combinations;
    }

private:
    std::vector<std::vector<int>> combinations;
    std::vector<int> combination;

    void backtracking(std::vector<int> &candidates, int target, int start, std::vector<bool> &used)
    {
        if (target == 0)
        {
            combinations.push_back(combination);
            return;
        }

        for (int i = start; i < candidates.size() && candidates[i] <= target; ++i)
        {
            if (i >= 1 && candidates[i] == candidates[i - 1] && !used[i - 1])
            {
                continue;
            }

            combination.push_back(candidates[i]);
            used[i] = true;
            backtracking(candidates, target - candidates[i], i + 1, used);
            used[i] = false;
            combination.pop_back();
        }
    }
};

// 7 10 1 2 7 6 1 5 8
int main()
{
    std::vector<int> candidates;
    int n, target;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int candidate;
        std::cin >> candidate;
        candidates.push_back(candidate);
    }
    std::cin >> target;

    Solution solution;
    std::vector<std::vector<int>> combinations = solution.combinationSum2(candidates, target);

    for (const auto &combination : combinations)
    {
        for (int candidate : combination)
        {
            std::cout << candidate << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
