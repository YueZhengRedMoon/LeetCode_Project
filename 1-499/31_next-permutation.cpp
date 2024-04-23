#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    void nextPermutation(std::vector<int>& a)
    {
        int n = a.size();
        // 从后向前找到第一个满足a[i] < a[i+1]的较小数a[i]
        int i;
        for (i = n - 2; i >= 0 && a[i] >= a[i + 1]; --i);
        // 找到顺序对(a[i], a[i+1])有a[i]<a[i+1]
        if (i >= 0)  // 此时a[i+1, n)一定是降序的
        {
            // 从后向前找到第一个满足a[i] < a[j]的较大数
            int j;
            for (j = n - 1; j > i && a[i] >= a[j]; --j);
            // 交换较小值a[i]与较大值a[j]，且交换后a[i+1, n)仍然是降序的
            std::swap(a[i], a[j]);
        }
        // 将a[i+1,n)的元素逆序
        std::reverse(a.begin() + i + 1, a.end());
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    solution.nextPermutation(nums);
    return 0;
}
