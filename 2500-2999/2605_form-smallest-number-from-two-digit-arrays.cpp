#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minNumber(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        int equalMin = 0x39c5bb;
        for (int num1 : nums1)
        {
            for (int num2 : nums2)
            {
                if (num1 == num2 && num1 < equalMin)
                {
                    equalMin = num1;
                }
            }
        }

        int min1 = *std::min_element(nums1.begin(), nums1.end());
        int min2 = *std::min_element(nums2.begin(), nums2.end());
        return std::min({min1 * 10 + min2, min2 * 10 + min1, equalMin});
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
