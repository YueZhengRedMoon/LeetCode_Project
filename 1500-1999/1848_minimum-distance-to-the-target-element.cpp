#include <iostream>
#include <vector>

class Solution
{
public:
    int getMinDistance(std::vector<int>& nums, int target, int start)
    {
        int n = nums.size();
        for (int i = start, j = start; i >= 0 || j < n; --i, ++j)
        {
            if (i >= 0 && nums[i] == target)
                return start - i;
            if (j < n && nums[j] == target)
                return j - start;
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}