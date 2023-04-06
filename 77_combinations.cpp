#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> combinations;
        std::vector<int> combination;
        backtracking(1, n, k, combinations, combination);
        return combinations;
    }

private:
    void backtracking(int begin, int end, int k,
                      std::vector<std::vector<int>> &combinations, std::vector<int> &combination)
    {
        if (begin > end)
        {
            return;
        }
        // 已经凑齐了k个数
        if (combination.size() == k)
        {
            combinations.push_back(combination);
            return;
        }
        // 将剩下的所有数加起来也不足以凑齐k个数
        if (combination.size() + end - begin + 1 < k)
        {
            return;
        }
        // 剩下的数加起来刚好可以凑齐k个数
        if (combination.size() + end - begin + 1 == k)
        {
            combinations.push_back(combination);
            for (int i = begin; i <= end; ++i)
            {
                combinations.back().push_back(i);
            }
            return;
        }

        // 选取begin加入组合
        combination.push_back(begin);
        backtracking(begin + 1, end, k, combinations, combination);
        combination.pop_back();

        // 不把begin加入组合
        backtracking(begin + 1, end, k, combinations, combination);
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> combinations;
        std::vector<int> combination;
        backtracking(1, n, k, combinations, combination);
        return combinations;
    }

private:
    void backtracking(int begin, int end, int k,
                      std::vector<std::vector<int>> &combinations, std::vector<int> &combination)
    {
        if (combination.size() == k)
        {
            combinations.push_back(combination);
            return;
        }
        for (int i = begin; i <= end; ++i)
        {
            // 剩下的数加起来都不足以凑齐k个数
            if (combination.size() + end - i + 1 < k)
            {
                break;
            }

            combination.push_back(i);
            backtracking(i + 1, end, k, combinations, combination);
            combination.pop_back();
        }
    }
};

int main()
{
    int n, k;
    std::cin >> n >> k;
    Solution solution;
    solution.combine(n, k);
    return 0;
}
