#include <iostream>
#include <vector>

class Solution
{
public:
    int findKOr(std::vector<int> &nums, int k)
    {
        int ans = 0;
        for (int i = 0; i < 31; ++i)
        {
            int cnt = 0;
            for (int num : nums)
            {
                cnt += ((num & (1 << i)) == (1 << i));
                if (cnt >= k)
                    break;
            }
            if (cnt >= k)
                ans |= (1 << i);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
