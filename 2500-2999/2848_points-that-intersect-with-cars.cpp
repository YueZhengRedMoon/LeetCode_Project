#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int numberOfPoints(std::vector<std::vector<int>> &nums)
    {
        bool isCovered[101]{};
        for (const std::vector<int> &num : nums)
        {
            for (int i = num[0]; i <= num[1]; ++i)
                isCovered[i] = true;
        }
        return std::count_if(std::begin(isCovered) + 1, std::end(isCovered), [](bool cover) {return cover;});
    }
};

class Solution2
{
public:
    int numberOfPoints(std::vector<std::vector<int>> &nums)
    {
        int maxEnd = 0;
        for (const std::vector<int> &num : nums)
        {
            if (num[1] > maxEnd)
                maxEnd = num[1];
        }

        std::vector<int> diff(maxEnd + 2, 0);
        for (const std::vector<int> &num : nums)
        {
            ++diff[num[0]];
            --diff[num[1] + 1];
        }

        int ans = 0;
        for (int i = 1; i <= maxEnd + 1; ++i)
        {
            diff[i] += diff[i - 1];
            ans += (diff[i] > 0);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
