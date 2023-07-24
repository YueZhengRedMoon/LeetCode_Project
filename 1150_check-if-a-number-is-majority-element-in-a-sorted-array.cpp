#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    bool isMajorityElement(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        std::unordered_map<int, int> count;
        for (int num : nums)
        {
            ++count[num];
        }
        return count[target] >= (n >> 1) + 1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}