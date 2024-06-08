#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>

class Solution
{
public:
    int maxOperations(std::vector<int>& nums)
    {
        int ans = 0, n = nums.size();
        std::unordered_set<long long> memo;
        auto hash = [](int i, int j, int score) -> long long {
            return i * 100000000LL + j * 10000LL + score;
        };
        std::function<void(int, int, int, int)> dfs = [&](int i, int j, int score, int cnt) {
            if (cnt > ans)
                ans = cnt;
            long long key = hash(i, j, score);
            if (i >= j || memo.find(key) != memo.end())
                return;

            memo.insert(key);

            ++cnt;
            // 选择前两个元素
            if (nums[i] + nums[i + 1] == score)
                dfs(i + 2, j, score, cnt);
            // 选择后两个元素
            if (nums[j - 1] + nums[j] == score)
                dfs(i, j - 2, score, cnt);
            // 选择第一个和最后一个元素
            if (nums[i] + nums[j] == score)
                dfs(i + 1, j - 1, score, cnt);
        };

        dfs(2, n - 1, nums[0] + nums[1], 1);
        dfs(0, n - 3, nums[n - 2] + nums[n - 1], 1);
        dfs(1, n - 2, nums[0] + nums[n - 1], 1);

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
