#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums)
    {
        std::vector<bool> branchUsed(nums.size(), false);
        backtracking(nums, branchUsed);
        return permutations;
    }

private:
    std::vector<int> permutation;
    std::vector<std::vector<int>> permutations;

    void backtracking(std::vector<int> &nums, std::vector<bool> &branchUsed)
    {
        if (permutation.size() == nums.size())
        {
            permutations.push_back(permutation);
            return;
        }

        bool levelUsed[21] = {0};
        for (int i = 0; i < nums.size(); ++i)
        {
            if (branchUsed[i] || levelUsed[nums[i] + 10])
            {
                continue;
            }

            levelUsed[nums[i] + 10] = true;
            permutation.push_back(nums[i]);
            branchUsed[i] = true;
            backtracking(nums, branchUsed);
            branchUsed[i] = false;
            permutation.pop_back();
        }
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums)
    {
        int n = nums.size();
        int capacity = 1;
        for (int i = 2; i <= n; ++i)
        {
            capacity *= i;
        }
        permutations.reserve(capacity);
        permutation.reserve(n);

        std::sort(nums.begin(), nums.end());
        std::vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return permutations;
    }

private:
    std::vector<int> permutation;
    std::vector<std::vector<int>> permutations;

    void backtracking(std::vector<int> &nums, std::vector<bool> &used)
    {
        if (permutation.size() == nums.size())
        {
            permutations.push_back(permutation);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            // nums[i] == nums[i - 1] && !used[i - 1]表示同一层同一数字已经遍历过，不用再遍历
            if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]))
            {
                continue;
            }

            permutation.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            used[i] = false;
            permutation.pop_back();
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
