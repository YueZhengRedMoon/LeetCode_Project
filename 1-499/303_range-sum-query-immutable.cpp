#include <iostream>
#include <vector>

class NumArray
{
public:
    NumArray(std::vector<int>& nums) : prefixSum(nums.size() + 1)
    {
        for (int i = 0; i < nums.size(); ++i)
        {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
    }

    int sumRange(int left, int right)
    {
        return prefixSum[right + 1] - prefixSum[left];
    }

private:
    std::vector<int> prefixSum;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
