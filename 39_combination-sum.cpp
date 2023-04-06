#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> combinations;
        std::vector<int> combination;
        backtracking(candidates, combinations, combination, 0, target);
        return combinations;
    }

private:
    void backtracking(std::vector<int> &candidates, std::vector<std::vector<int>> &combinations,
                      std::vector<int> &combination, int start, int target)
    {
        if (target == 0)
        {
            combinations.push_back(combination);
            return;
        }
        for (int i = start; i < candidates.size(); ++i)
        {
            int j = 0;
            for (j = 1; j * candidates[i] <= target; ++j)
            {
                combination.push_back(candidates[i]);
                backtracking(candidates, combinations, combination, i + 1, target - j * candidates[i]);
            }
            for (int k = 0; k < j - 1; ++k)
            {
                combination.pop_back();
            }
        }
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int> &candidates, int target)
    {
        std::vector<std::vector<int>> combinations;
        std::vector<int> combination;
        std::sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, combinations, combination);
        return combinations;
    }

private:
    void backtracking(std::vector<int> &candidates, int target, int startIndex,
                      std::vector<std::vector<int>> &combinations, std::vector<int> &combination)
    {
        if (target == 0)
        {
            combinations.push_back(combination);
            return;
        }

        for (int i = startIndex; i < candidates.size() && candidates[i] <= target; ++i)
        {
            combination.push_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i, combinations, combination);
            combination.pop_back();
        }
    }
};

int main()
{
    std::vector<int> candidates;
    int n, num, target;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        candidates.push_back(num);
    }
    std::cin >> target;

    Solution2 solution;
    std::vector<std::vector<int>> combinations = solution.combinationSum(candidates, target);
    for (auto &combination : combinations)
    {
        for (int value : combination)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
