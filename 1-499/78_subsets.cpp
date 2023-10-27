#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums)
    {
        backtracking(nums, 0);
        return subsets_;
    }

private:
    std::vector<int> subset_;
    std::vector<std::vector<int>> subsets_;

    void backtracking(std::vector<int> &nums, int start)
    {
        if (start == nums.size())
        {
            subsets_.push_back(subset_);
            return;
        }

        // 选取nums[i]
        subset_.push_back(nums[start]);
        backtracking(nums, start + 1);
        subset_.pop_back();

        // 不选取nums[i]
        backtracking(nums, start + 1);
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums)
    {
        backtracking(nums, 0);
        return subsets_;
    }

private:
    std::vector<int> subset_;
    std::vector<std::vector<int>> subsets_;

    void backtracking(std::vector<int> &nums, int start)
    {
        // 收集子集
        subsets_.push_back(subset_);

//        if (start == nums.size())
//        {
//            return;
//        }

        for (int i = start; i < nums.size(); ++i)
        {
            subset_.push_back(nums[i]);
            backtracking(nums, i + 1);
            subset_.pop_back();
        }
    }
};

class Solution3
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int> &nums)
    {
        int set = 0;
        for (int num : nums)
        {
            set |= 1 << (num + 10);
        }

        std::vector<std::vector<int>> ans;
        ans.emplace_back();
        for (int sub = set; sub; sub = (sub - 1) & (set))
        {
            std::vector<int> subset;
            int bit = sub;
            int j = 0;
            while (bit)
            {
                if (bit & 1)
                {
                    subset.push_back(j - 10);
                }
                ++j;
                bit >>= 1;
            }
            ans.push_back(std::move(subset));
        }

        return ans;
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
    std::vector<std::vector<int>> subsets = solution.subsets(nums);
    for (const auto &subset : subsets)
    {
        printVector(subset);
    }
    return 0;
}
