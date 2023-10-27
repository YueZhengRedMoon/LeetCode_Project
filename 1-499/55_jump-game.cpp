#include <iostream>
#include <vector>

class Solution
{
public:
    bool canJump(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return true;
        }

        // 只有当nums中存在0时，才可能出现无法到达最后一个位置的情况
        // 当遇到0时，必须要能够从0前面的某个位置跳过这个0
        int zeroIndex = -1; // zeroIndex表示当前某个位置存在0还无法跳过，如zeroIndex等于-1，则表示当前没有0无法跳过
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            if (nums[i] == 0 && zeroIndex == -1)
            {
                zeroIndex = i;
            }
            else if (zeroIndex != -1    // 当前存在没有跳过的0
                    && (i + nums[i] > zeroIndex // 从该位置可以跳过那个0
                    // 从该位置可以刚好跳到0，且那个0正好是最后一个位置
                    || (zeroIndex == nums.size() - 1 && i + nums[i] == zeroIndex)))
            {
                zeroIndex = -1;
            }
        }
        return zeroIndex == -1;
    }
};

class Solution2
{
public:
    bool canJump(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return true;
        }

        int cover = 0;
        for (int i = 0; i <= cover; ++i)
        {
            cover = std::max(cover, i + nums[i]);
            if (cover >= nums.size() - 1)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
