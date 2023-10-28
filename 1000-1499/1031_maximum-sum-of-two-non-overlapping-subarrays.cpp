#include <iostream>
#include <vector>
#include <numeric>
#include "../debug/debug.h"

class Solution
{
public:
    struct SubArray
    {
        SubArray(int b = 0, int e = 0, int s = 0) : begin(b), end(e), sum(s) {}

        int begin;
        int end;
        int sum;
    };

    int maxSumTwoNoOverlap(std::vector<int> &nums, int firstLen, int secondLen)
    {
        int numsSize = nums.size();
        std::vector<std::vector<int>> sum(numsSize, std::vector<int>(numsSize, 0));

        std::vector<SubArray> firstSubArray;
        firstSubArray.reserve(numsSize - firstLen + 1);
        std::vector<SubArray> secondSubArray;
        secondSubArray.reserve(numsSize - secondLen + 1);

        for (int i = 0; i < numsSize; ++i)
        {
            sum[i][i] = nums[i];
            if (firstLen == 1)
            {
                firstSubArray.emplace_back(i, i, nums[i]);
            }
            if (secondLen == 1)
            {
                secondSubArray.emplace_back(i, i, nums[i]);
            }
            for (int j = i + 1; j < numsSize; ++j)
            {
                sum[i][j] = sum[i][j - 1] + nums[j];

                if (j - i + 1 == firstLen)
                {
                    firstSubArray.emplace_back(i, j, sum[i][j]);
                }
                else if (j - i + 1 == secondLen)
                {
                    secondSubArray.emplace_back(i, j, sum[i][j]);
                }
            }
        }

        int maxSum = 0;
        for (int i = 0; i < firstSubArray.size(); ++i)
        {
            for (int j = 0; j < secondSubArray.size(); ++j)
            {
                if (isNotOverlapped(firstSubArray[i], secondSubArray[j]))
                {
                    maxSum = std::max(maxSum, firstSubArray[i].sum + secondSubArray[j].sum);
                }
            }
        }

        return maxSum;
    }

private:
    bool isNotOverlapped(const SubArray &lhs, const SubArray &rhs)
    {
        if (lhs.begin > rhs.begin)
        {
            return rhs.end < lhs.begin;
        }
        else
        {
            return lhs.end < rhs.begin;
        }
    }
};

class Solution2
{
public:
    int maxSumTwoNoOverlap(std::vector<int> &nums, int firstLen, int secondLen)
    {
        return std::max(help(nums, firstLen, secondLen), help(nums, secondLen, firstLen));
    }

private:
    int help(std::vector<int> &nums, int firstLen, int secondeLen)
    {
        int sumL = std::accumulate(nums.begin(), nums.begin() + firstLen, 0);
        int maxSumL = sumL;
        int sumR = std::accumulate(nums.begin() + firstLen, nums.begin() + firstLen + secondeLen, 0);
        int result = maxSumL + sumR;

        for (int i = firstLen + secondeLen, j = firstLen; i < nums.size(); ++i, ++j)
        {
            sumL += nums[j] - nums[j - firstLen];
            if (sumL > maxSumL)
                maxSumL = sumL;
            sumR += nums[i] - nums[i - secondeLen];
            result = std::max(result, maxSumL + sumR);
        }

        return result;
    }
};

int main()
{
    std::vector<int> nums{0,6,5,2,2,5,1,9,4};
    Solution solution;
    int result = solution.maxSumTwoNoOverlap(nums, 1, 2);
    std::cout << result << std::endl;
    return 0;
}