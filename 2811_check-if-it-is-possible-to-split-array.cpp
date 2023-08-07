#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution
{
public:
    bool canSplitArray(std::vector<int> &nums, int m)
    {
        subArrSum = m;
        len = nums.size();
        prefix.resize(len);
        prefix[0] = nums[0];
        for (int i = 1; i < len; ++i)
        {
            prefix[i] = prefix[i - 1] + nums[i];
        }
        return dfs(nums, 0, len - 1);
    }

private:
    int subArrSum;
    int len;
    std::vector<int> prefix;
    std::unordered_set<int> memo;

    bool dfs(std::vector<int> &nums, int l, int r)
    {
        if (r - l <= 1)
            return true;
        if (sum(l, r) <= subArrSum)
            return false;

        int key = hash(l, r);
        auto mapIt = memo.find(key);
        if (mapIt != memo.end())
            return true;

        int leftSum = sum(l, r - 1);
        if (leftSum >= subArrSum && dfs(nums, l, r - 1))
        {
            memo.emplace(key);
            return true;
        }
        int rightSum = sum(l + 1, r);
        if (rightSum >= subArrSum && dfs(nums, l + 1, r))
        {
            memo.emplace(key);
            return true;
        }

        int target = prefix[l] + subArrSum - nums[l];
        auto begin = prefix.begin() + l;
        auto end = prefix.begin() + r + 1;
        auto it = std::lower_bound(begin, end, target);
        if (it == end || it == nums.begin() + r)
            return false;

        // prefix[mid] >= prefix[l] + subArrSum - nums[l]
        // prefix[mid] - prefix[l] >= subArrSum - nums[l]
        // sum[l+1:mid] >= subArrSum - nums[l]
        // sum[l:mid] >= m
        int mid = it - begin;
        leftSum = sum(l, mid);
        rightSum = sum(mid + 1, r);
        for (int i = mid; i < r && (rightSum >= subArrSum || i + 1 == r); ++i)
        {
            if (dfs(nums, l, i) && dfs(nums, i + 1, r))
            {
                memo.emplace(key);
                return true;
            }

            leftSum += nums[i + 1];
            rightSum -= nums[i + 1];
        }

        return false;
    }

    int sum(int l, int r)
    {
        return l == 0 ? prefix[r] : prefix[r] - prefix[l - 1];
    }

    int hash(int l, int r)
    {
        return l * 100 + r;
    }
};

class Solution2
{
public:
    bool canSplitArray(std::vector<int> &nums, int m)
    {
        int n = nums.size();
        if (n <= 2)
            return true;

        for (int i = 1; i < n; ++i)
        {
            if (nums[i - 1] + nums[i] >= m)
                return true;
        }

        return false;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 1, 1};
    int m = 4;
    bool ans = solution.canSplitArray(nums, m);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}