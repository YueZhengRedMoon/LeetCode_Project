#include <iostream>
#include <vector>

class Solution
{
public:
    long long findTheArrayConcVal(std::vector<int> &nums)
    {
        long long ans = 0;
        int n = nums.size();
        for (int i = 0, j = n - 1; i <= j; ++i, --j)
        {
            if (i == j)
            {
                ans += nums[i];
            }
            else
            {
                std::string s = std::to_string(nums[i]);
                s.append(std::to_string(nums[j]));
                ans += std::stoll(s);
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
