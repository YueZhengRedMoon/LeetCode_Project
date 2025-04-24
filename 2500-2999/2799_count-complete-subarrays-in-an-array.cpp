#include <iostream>
#include <vector>
#include <cstring>

const int MAX_NUM = 2001;
bool isInNums[MAX_NUM];
int counter[MAX_NUM];

class Solution
{
public:
    int countCompleteSubarrays(std::vector<int>& nums)
    {
        std::memset(isInNums, 0, sizeof(isInNums));
        std::memset(counter, 0, sizeof(counter));

        int kind = 0;   // 整个数组中不同元素的数目
        for (int x : nums)
        {
            if (!isInNums[x])
            {
                isInNums[x] = true;
                ++kind;
            }
        }

        int n = nums.size(), ans = 0, cnt = 0;  // cnt:当前子数组中不同元素的数目
        for (int i = 0, j = 0; j < n; ++j)
        {
            int x = nums[j];
            if (counter[x] == 0)
            {
                ++cnt;
            }
            ++counter[x];

            while (cnt == kind)
            {
                ans += n - j;
                x = nums[i++];
                if (--counter[x] == 0)
                {
                    --cnt;
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
