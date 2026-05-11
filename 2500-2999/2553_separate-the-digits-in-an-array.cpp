#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> separateDigits(std::vector<int>& nums)
    {
        std::vector<int> ans;
        for (int num : nums)
        {
            std::vector<int> temp;
            while (num)
            {
                temp.push_back(num % 10);
                num /= 10;
            }
            std::reverse(temp.begin(), temp.end());
            ans.insert(ans.end(), temp.begin(), temp.end());
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}