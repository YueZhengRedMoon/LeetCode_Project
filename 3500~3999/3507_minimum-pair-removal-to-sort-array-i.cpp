#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumPairRemoval(std::vector<int>& nums)
    {
        int ans = 0, n = nums.size();
        bool isAsc;  // nums是否已经是非递减排序
        do
        {
            isAsc = true;
            int pIdx = 0;   // nums[pIdx-1],nums[pIdx]的和最小
            int minSum = INT_MAX;
            for (int i = 1; i < n; ++i)
            {
                if (nums[i] < nums[i - 1])
                {
                    isAsc = false;
                }
                if (nums[i] + nums[i - 1] < minSum)
                {
                    minSum = nums[i] + nums[i - 1];
                    pIdx = i;
                }
            }

            if (!isAsc)
            {
                // 将nums[pIdx-1]和nums[pIdx]替换为minSum
                nums[pIdx - 1] = minSum;
                --n;
                for (int i = pIdx; i < n; ++i)
                {
                    nums[i] = nums[i + 1];
                }
                ++ans;
            }
        } while (!isAsc);
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}