#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        std::vector<std::vector<int>> combinations;
        if (n > 45)
        {
            return combinations;
        }

        std::vector<int> combination;
        backtracking(combination, combinations,1, k, n);
        return combinations;
    }

private:
    void backtracking(std::vector<int> &combination, std::vector<std::vector<int>> &combinations,
                      int begin, int k, int n)
    {
        if (n == 0 && combination.size() == k)
        {
            combinations.push_back(combination);
            return;
        }
        if (n < 0 || combination.size() >= k)
        {
            return;
        }
        for (int i = begin; i <= 9; ++i)
        {
            // 加上剩下的数无法凑齐k个数
            if (combination.size() + 10 - i < k)
            {
                break;
            }

            combination.push_back(i);
            backtracking(combination, combinations, i + 1, k, n - i);
            combination.pop_back();
        }
    }
};

/** 枚举法 */
class Solution2
{
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        std::vector<std::vector<int>> combinations;
        if (n > 45)
        {
            // 1~9所有数加起来等于45，超过45的数无法表示
            return combinations;
        }

        std::vector<int> combination;

        // 枚举0~2^9-1种状态
        for (int mask = 0; mask < (1 << 9); ++mask)
        {
            if (check(mask, k, n, combination))
            {
                combinations.push_back(combination);
            }
        }

        return combinations;
    }

private:
    bool check(int mask, int k, int n, std::vector<int> &combination)
    {
        combination.clear();
        int sum = 0;
        // 检查枚举状态mask是否使用了数字i
        for (int i = 0; i < 9; ++i)
        {
            // 使用了数字i
            if ((1 << i) & mask)
            {
                combination.push_back(i + 1);
                sum += i;
            }
        }
        return  sum == n && combination.size() == k;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
