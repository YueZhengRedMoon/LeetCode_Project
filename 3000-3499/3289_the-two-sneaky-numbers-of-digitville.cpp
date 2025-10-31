#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> getSneakyNumbers(std::vector<int>& nums)
    {
        int n = nums.size() - 2;
        // 将nums中所有数异或后，在依次异或[0, n)中的所有数，这样原本出现1次的数就会变为出现2次，异或和为0
        // 原本出现2次的数变为出现3次，进行该操作后的结果等于两个原本出现2次的数的异或和
        int xorAll = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            xorAll ^= i ^ nums[i];
        }
        xorAll ^= n ^ (n + 1);  // n 和 n+1 在上面的循环中多异或了，在此消除

        // 假设出现2次的数为x, y，则x^y的结果中一定有一位为1（在此取最低位的1），x和y在该位的值一个是1一个是0
        int shift = __builtin_ctz(xorAll);  // xorAll尾随0的个数（xorAll最低位的1的序号）

        // 将nums中的数分组，shift位为1的分为一组，shift位为0的分为一组，这样x和y必定被分到两组中
        // 且两组中除x和y以外的数都正好出现2次
        // 求两个组的异或和，就能计算出x与y
        std::vector<int> ans(2);
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i < n)
            {
                ans[(i >> shift) & 1] ^= i;
            }
            ans[(nums[i] >> shift) & 1] ^= nums[i];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}