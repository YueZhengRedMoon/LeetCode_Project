#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int> &nums)
    {
        std::vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return permutations;
    }

private:
    std::vector<int> permutation;
    std::vector<std::vector<int>> permutations;

    void backtracking(std::vector<int> &nums, std::vector<bool> &used)
    {
        unsigned int numsSize = nums.size();
        if (permutation.size() == numsSize)
        {
            permutations.push_back(permutation);
            return;
        }

        for (unsigned int i = 0; i < numsSize; ++i)
        {
            if (used[i])
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

    Solution solution;
    std::vector<std::vector<int>> permutations = solution.permute(nums);
    for (const auto& permutation : permutations)
    {
        for (int value : permutation)
        {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
