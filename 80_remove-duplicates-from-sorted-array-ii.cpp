#include <iostream>
#include <vector>

class Solution
{
public:
    int removeDuplicates(std::vector<int> &nums)
    {
        if (nums.size() <= 2)
        {
            return nums.size();
        }

        int slow = 2;
        for (int i = 2; i < nums.size(); ++i)
        {
            if (nums[i] != nums[slow - 1] || nums[i] != nums[slow - 2])
            {
                nums[slow++] = nums[i];
            }
        }
        return slow;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
