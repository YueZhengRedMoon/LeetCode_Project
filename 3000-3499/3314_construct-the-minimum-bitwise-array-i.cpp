#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

const int MAX_P = 1001;
bool isPrime[MAX_P];
std::unordered_map<int, int> ansMap;
int init = [](){
    std::fill(std::begin(isPrime) + 2, std::end(isPrime), true);
    for (int i = 2; i < MAX_P; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i + i; j < MAX_P; j += i)
            {
                isPrime[j] = false;
            }

            int res = -1;
            for (int k = 0; k < i; ++k)
            {
                if ((k | (k + 1)) == i)
                {
                    res = k;
                    break;
                }
            }
            ansMap[i] = res;
            std::cout << "ansMap[" << i << "] = " << res << std::endl;
        }
    }
    return 0;
}();

class Solution
{
public:
    std::vector<int> minBitwiseArray(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            ans[i] = ansMap[nums[i]];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}