#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> pivotArray(std::vector<int>& nums, int pivot)
    {
        std::vector<int> a, b, c;
        for (int x : nums)
        {
            if (x < pivot)
                a.push_back(x);
            else if (x == pivot)
                b.push_back(x);
            else
                c.push_back(x);
        }
        a.insert(a.end(), b.begin(), b.end());
        a.insert(a.end(), c.begin(), c.end());
        return a;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}