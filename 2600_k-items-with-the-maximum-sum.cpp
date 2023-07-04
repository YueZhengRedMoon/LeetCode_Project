#include <iostream>
#include <vector>

class Solution
{
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k)
    {
        int ans = 0;
        if (numOnes >= k)
        {
            return k;
        }
        else
        {
            ans += numOnes;
            k -= numOnes;
        }
        if (numZeros >= k)
        {
            return ans;
        }
        else
        {
            k -= numZeros;
        }
        ans -= k;
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}