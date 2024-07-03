#include <iostream>
#include <vector>

const int MAX_NUM = 101;
bool isPrime[MAX_NUM];
int init = [](){
    std::fill(std::begin(isPrime) + 2, std::end(isPrime), true);
    for (int i = 2; i < MAX_NUM; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i + i; j < MAX_NUM; j += i)
                isPrime[j] = false;
        }
    }
    return 0;
}();

class Solution
{
public:
    int maximumPrimeDifference(std::vector<int>& nums)
    {
        int firstPrimeIdx = -1, ans = 0, n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            if (isPrime[nums[i]])
            {
                if (firstPrimeIdx == -1)
                    firstPrimeIdx = i;
                ans = i - firstPrimeIdx;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
