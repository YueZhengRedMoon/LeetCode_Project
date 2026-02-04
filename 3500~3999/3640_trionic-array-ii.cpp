#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxSumTrionic(std::vector<int>& nums)
    {
        int n = nums.size();
        long long ans = LLONG_MIN;
        for (int i = 0; i < n;)
        {
            // 第一段:[start,peak]
            int start = i;
            for (++i; i < n && nums[i - 1] < nums[i]; ++i);
            if (i == start + 1) // 第一段至少要有两个数
            {
                continue;
            }

            // 第二段:[peak,bottom]
            int peak = i - 1;   // 此时nums[i-1]>=nums[i]
            long long res = nums[peak - 1] + nums[peak];    // 第一段的最后两个数必选
            for (; i < n && nums[i - 1] > nums[i]; ++i)
            {
                res += nums[i]; //  第二段的所有元素必选https://drive.google.com/file/d/1nTi2YK-O8BwF_6rBdC996f1CTDhVGHA8/view?usp=sharing
            }
            if (i == peak + 1 || i == n || nums[i - 1] == nums[i])  // 第二段至少要有两个数，第三段至少要有两个数
            {
                continue;
            }

            // 第三段，从bottom开始
            int bottom = i - 1; // 此时nums[i-1] < nums[i]
            res += nums[i]; // 第三段的前两个数必选（第一个数在上面的循环中加了）
            // 从第三段的第三个数往右，计算最大元素和
            long long maxSum = 0, sum = 0;
            for (++i; i < n && nums[i - 1] < nums[i]; ++i)
            {
                sum += nums[i];
                if (sum > maxSum)
                {
                    maxSum = sum;
                }
            }
            res += maxSum;

            // 从第一段的倒数第三个数往左，计算最大元素和
            maxSum = 0, sum = 0;
            for (int j = peak - 2; j >= start; --j)
            {
                sum += nums[j];
                if (sum > maxSum)
                {
                    maxSum = sum;
                }
            }
            res += maxSum;

            if (res > ans)
            {
                ans = res;
            }

            i = bottom; // 第三段的起点也是下一个极大三段式子数组的第一段的起点
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}