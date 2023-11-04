#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution
{
public:
    int findMaximumXOR(std::vector<int> &nums)
    {
        int n = nums.size();
        int maxNum = *std::max_element(nums.begin(), nums.end());
        if (maxNum == 0)
            return 0;

        int highBits = 32 - __builtin_clz(maxNum) - 1;
        int ans = 0, mask = 0;
        // 依次判断答案的每一位是否可以为1
        for (int i = highBits; i >= 0; --i)
        {
            mask |= 1 << i;                 // 用来将num的低位全抹0
            int newAns = ans | (1 << i);    // 如果答案的第i位可以位1，则当前答案的值将变为newAns
            std::unordered_set<int> seen;
            // 判断答案的第i位是否可以为1
            // 将nums中所有数i位之下的位都置0，检查其中是否存在两个数x, y使得x ^ y = newAns
            // 如果存在，ans的第i位可以为1，否则，ans的第i位只能为0
            for (int num : nums)
            {
                int x = num & mask; // 将num的低位全抹0
                // x ^ y = newAns -> y = newAns ^ x
                if (seen.find(newAns ^ x) != seen.end())
                {
                    ans = newAns;
                    break;
                }
                seen.insert(x);
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
