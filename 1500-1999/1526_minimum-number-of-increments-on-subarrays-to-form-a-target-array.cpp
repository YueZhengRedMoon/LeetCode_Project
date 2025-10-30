#include <iostream>
#include <vector>

class Solution
{
public:
    int minNumberOperations(std::vector<int>& target)
    {
        // 设target的差分数组为d，全0数组initial的差分数组为d0(也是全0)数组
        // 将initial数组变为target等价于将d0变为d，每次操作等价于：
        // - 如果操作的不是initial的后缀，等价于修改d0两个位置上的数，左边+1，右边-1
        // - 如果操作的是initial的后缀，等价于把d0中的某个数+1
        // 无论如何操作，每次都会将d0中的一个数+1
        // 因此最少的操作次数即为差分数组d中所有正数之和
        int ans = target[0];
        for (int i = 1; i < target.size(); ++i)
        {
            ans += std::max(target[i] - target[i - 1], 0);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}