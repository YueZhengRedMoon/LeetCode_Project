#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> addNegabinary(std::vector<int> &arr1, std::vector<int> &arr2)
    {
        int i = arr1.size() - 1, j = arr2.size() - 1;
        int carry = 0;
        std::vector<int> ans;
        while (i >= 0 || j >= 0 || carry)
        {
            int x = carry;
            if (i >= 0)
                x += arr1[i];
            if (j >= 0)
                x += arr2[j];
            if (x >= 2)
            {
                ans.push_back(x - 2);
                carry = -1;
            }
            else if (x >= 0)
            {
                ans.push_back(x);
                carry = 0;
            }
            else
            {
                ans.push_back(1);
                carry = 1;
            }
            --i;
            --j;
        }
        while (ans.size() > 1 && ans.back() == 0)
        {
            ans.pop_back();
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}