#include <iostream>
#include <vector>
#include <algorithm>

constexpr long long MAX_HIGH = 1'000'000'000LL;
constexpr long long MIN_LOW = 10;
std::vector<int> nums;

void dfs(long long num)
{
    if (num > MAX_HIGH)
    {
        return;
    }

    if (num > MIN_LOW)
    {
        nums.push_back((int) num);
    }
    int digit = num % 10;
    if (digit < 9)
    {
        dfs(num * 10 + digit + 1);
    }
}

int init = [](){
    for (int i = 1; i < 9; ++i)
    {
        dfs(i);
    }
    std::sort(nums.begin(), nums.end());
    return 0;
}();

class Solution
{
public:
    std::vector<int> sequentialDigits(int low, int high)
    {
        auto begin = std::lower_bound(nums.begin(), nums.end(), low);
        auto end = std::upper_bound(nums.begin(), nums.end(), high);
        return std::vector<int>(begin, end);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}