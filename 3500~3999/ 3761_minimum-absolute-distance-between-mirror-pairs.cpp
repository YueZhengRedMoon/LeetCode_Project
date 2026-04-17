#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minMirrorPairDistance(std::vector<int>& nums)
    {
        int ans = INT_MAX, n = nums.size();
        std::unordered_map<int, int> pos;
        for (int j = 0; j < n; ++j)
        {
            auto it = pos.find(nums[j]);
            if (it != pos.end())
            {
                int i = it->second;
                ans = std::min(ans, j - i);
            }

            int reverseNum = reverse(nums[j]);
            pos[reverseNum] = j;
        }
        return ans == INT_MAX ? -1 : ans;
    }

private:
    int reverse(int num)
    {
        int res = 0;
        while (num)
        {
            res = res * 10 + num % 10;
            num /= 10;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}