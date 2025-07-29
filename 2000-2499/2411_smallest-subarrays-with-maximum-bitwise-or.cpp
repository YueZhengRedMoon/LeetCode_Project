#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> smallestSubarrays(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> ans(n);

        std::vector<int> totalOr(n);    // totalOr[i]:nums[i, n)的所有元素按位或的值
        totalOr[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            totalOr[i] = nums[i] | totalOr[i + 1];
        }

        const int BIT_LEN = 30;     // nums[i]<= 10^9，最多只需要30个比特位就能表示所有的nums[i]
        int bitCnt[BIT_LEN]{0};
        auto updateBitCnt = [&](int val, int delta) {
            int i = 0;
            while (val)
            {
                if (val & 1)
                {
                    bitCnt[i] += delta;
                }
                val >>= 1;
                ++i;
            }
        };

        int curOr = 0;
        for (int i = 0, j = 0; i < n; ++i)
        {
            if (totalOr[i] == 0)
            {
                ans[i] = 1;
                j = i + 1;
                continue;
            }

            while (curOr < totalOr[i])
            {
                curOr |= nums[j];
                updateBitCnt(nums[j], 1);
                ++j;
            }

            ans[i] = j - i;

            updateBitCnt(nums[i], -1);
            curOr = 0;
            for (int k = 0; k < BIT_LEN; ++k)
            {
                if (bitCnt[k])
                {
                    curOr |= (1 << k);
                }
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
