#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        std::vector<int> ans(2);
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (i > 0 && numbers[i] == numbers[i - 1])
                continue;
            auto it = std::lower_bound(numbers.begin() + i + 1, numbers.end(), target - numbers[i]);
            if (it != numbers.end() && numbers[i] + *it == target)
            {
                ans[0] = i + 1;
                ans[1] = it - numbers.begin() + 1;
                break;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}