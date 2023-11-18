#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int maximumSum(std::vector<int> &nums)
    {
        const int ninf = -0x3f3f3f3f;
        int ans = -1;
        // key:数位和, value:(数位和为key的最大的数，数位和为key的第二大的数)
        std::unordered_map<int, std::pair<int, int>> topNum;

        for (int num : nums)
        {
            int sum = sumOfDigits(num);
            auto it = topNum.find(sum);
            if (it == topNum.end())
            {
                topNum[sum] = {num, ninf};
            }
            else
            {
                std::pair<int, int> &top = it->second;
                if (num >= top.first)
                {
                    top.second = top.first;
                    top.first = num;
                    ans = std::max(ans, top.first + top.second);
                }
                else if (num > top.second)
                {
                    top.second = num;
                    ans = std::max(ans, top.first + top.second);
                }
            }
        }

        return ans;
    }

private:
    int sumOfDigits(int num)
    {
        int sum = 0;
        while (num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
