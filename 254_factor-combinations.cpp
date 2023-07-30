#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> getFactors(int n)
    {
        backtracking(n, std::vector<int>(), n, 2);
        return std::vector<std::vector<int>>(ans.begin(), ans.end());
    }

private:
    std::set<std::vector<int>> ans;

    void backtracking(int num, std::vector<int> factors, int n, int lastFactor)
    {
        if (num == 1 && !factors.empty())
        {
            ans.emplace(std::move(factors));
            std::sort(factors.begin(), factors.end());
            return;
        }

        bool isPrime = true;
        for (int f = lastFactor; f * 2 <= num; ++f)
        {
            if (num % f == 0)
            {
                std::vector<int> newFactors(factors);
                newFactors.push_back(f);
                backtracking(num / f, newFactors, n, f);
                isPrime = false;
            }
        }

        if (isPrime && num != n)
        {
            factors.push_back(num);
            std::sort(factors.begin(), factors.end());
            ans.emplace(std::move(factors));
        }
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> getFactors(int n)
    {
        backtracking(n, 2);
        return ans;
    }

private:
    std::vector<std::vector<int>> ans;
    std::vector<int> factors;

    void backtracking(int n, int f)
    {
        for (int i = f; i * i <= n; ++i)
        {
            if (n % i == 0)
            {
                factors.push_back(i);
                factors.push_back(n / i);
                ans.push_back(factors);
                factors.pop_back();
                backtracking(n / i, i);
                factors.pop_back();
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}