#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> findSubsequences(std::vector<int> &nums)
    {
        backtracking(nums, 0);
        return sequences;
    }

private:
    std::vector<int> sequence;
    std::vector<std::vector<int>> sequences;

    void backtracking(std::vector<int> &nums, int start)
    {
        if (sequence.size() > 1)
        {
            sequences.push_back(sequence);
        }

        bool used[201] = {false};
        for (int i = start; i < nums.size(); ++i)
        {
            // 同一父节点下不能使用相同的值
            int key = hash(nums[i]);
            if (used[key] || (!sequence.empty() && nums[i] < sequence.back()))
            {
                continue;
            }

            used[key] = true;
            sequence.push_back(nums[i]);
            backtracking(nums, i + 1);
            sequence.pop_back();
        }
    }

    inline int hash(int key)
    {
        return key + 100;
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
    std::vector<std::vector<int>> subsets = solution.findSubsequences(nums);
    for (const auto &subset : subsets)
    {
        printVector(subset);
    }
    return 0;
}
