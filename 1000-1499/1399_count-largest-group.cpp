#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int countLargestGroup(int n)
    {
        std::unordered_map<int, int> group;
        int maxGroupSize = 0;   // 最大的组中有多少个数字
        int maxGroupCnt = 0;    // 有多少个数字数目并列最多的最大组
        for (int i = 1; i <= n; ++i)
        {
            int& size = group[digitSum(i)];
            ++size;

            if (size > maxGroupSize)
            {
                maxGroupSize = size;
                maxGroupCnt = 1;
            }
            else if (size == maxGroupSize)
            {
                ++maxGroupCnt;
            }
        }
        return maxGroupCnt;
    }

private:
    int digitSum(int num)
    {
        int sum = 0;
        while (num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
