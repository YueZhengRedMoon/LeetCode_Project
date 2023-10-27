#include <iostream>
#include <vector>
#include <sstream>

class Solution
{
public:
    std::vector<std::string> summaryRanges(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<std::string> ans;
        if (n == 0) return ans;

        int start = 0;
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] != nums[i - 1] + 1)
            {
                std::ostringstream oss;
                if (start == i - 1)
                {
                    oss << nums[start];
                }
                else
                {
                    oss << nums[start] << "->" << nums[i - 1];
                }
                ans.emplace_back(oss.str());
                start = i;
            }
        }

        std::ostringstream oss;
        if (start == n - 1)
        {
            oss << nums[start];
        }
        else
        {
            oss << nums[start] << "->" << nums[n - 1];
        }
        ans.emplace_back(oss.str());

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}