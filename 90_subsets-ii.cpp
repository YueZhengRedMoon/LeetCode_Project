#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums)
    {
        used.resize(nums.size(), false);
        std::sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return subsets;
    }

private:
    std::vector<bool> used;
    std::vector<int> subset;
    std::vector<std::vector<int>> subsets;

    void backtracking(std::vector<int> &nums, int index)
    {
        if (index == nums.size())
        {
            subsets.push_back(subset);
            return;
        }

        // 选取当前元素
        if (index == 0 || nums[index] != nums[index - 1] || used[index - 1])
        {
            subset.push_back(nums[index]);
            used[index] = true;
            backtracking(nums, index + 1);
            used[index] = false;
            subset.pop_back();
        }

        // 不选取当前元素
        backtracking(nums, index + 1);
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums)
    {
        used.resize(nums.size(), false);
        std::sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return subsets;
    }

private:
    std::vector<bool> used;
    std::vector<int> subset;
    std::vector<std::vector<int>> subsets;

    void backtracking(std::vector<int> &nums, int start)
    {
        subsets.push_back(subset);

        for (int i = start; i < nums.size(); ++i)
        {
            // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
            // used[i - 1] == false，说明同一树层nums[i - 1]使用过
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
            {
                continue;
            }

            subset.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1);
            used[i] = false;
            subset.pop_back();
        }
    }
};

/** 使用set去重 */
class Solution3
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return subsets;
    }

private:
    std::vector<int> subset;
    std::vector<std::vector<int>> subsets;

    void backtracking(std::vector<int> &nums, int start)
    {
        subsets.push_back(subset);
        std::unordered_set<int> unorderedSet;
        for (int i = start; i < nums.size(); ++i)
        {
            // 确保这一层每一个数只使用一次
            if (unorderedSet.find(nums[i]) != unorderedSet.end())
            {
                continue;
            }

            unorderedSet.insert(nums[i]);
            subset.push_back(nums[i]);
            backtracking(nums, i + 1);
            subset.pop_back();
        }
    }
};

void printVector(const std::vector<int>& nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> nums;
    int n, num;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> num;
        nums.push_back(num);
    }

    Solution3 solution;
    std::vector<std::vector<int>> subsets = solution.subsetsWithDup(nums);
    for (const auto &subset : subsets)
    {
        printVector(subset);
    }
    return 0;
}
