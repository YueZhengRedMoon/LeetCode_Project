#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumRightShifts(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return 0;

        int minNum = nums[0], minNumIndex = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] < minNum)
            {
                minNum = nums[i];
                minNumIndex = i;
            }
        }

        for (int i = minNumIndex, next = (i + 1) % n; nums[next] != minNum; i = (i + 1) % n, next = (i + 1) % n)
        {
            if (nums[i] > nums[next])
                return -1;
        }

        return (n - minNumIndex) % n;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
