#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    int pivotInteger(int n)
    {
        int left = 1, right = n;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            int leftSum = sum(1, mid);
            int rightSum = sum(mid, n);
            if (leftSum > rightSum)
            {
                right = mid - 1;
            }
            else if (leftSum < rightSum)
            {
                left = mid + 1;
            }
            else
            {
                return mid;
            }
        }
        return -1;
    }

private:
    inline int sum(int a1, int a2)
    {
        return (a1 + a2) * (a2 - a1 + 1) / 2;
    }
};

class Solution2
{
public:
    int pivotInteger(int n)
    {
        // leftSum = 1 + 2 + …… + x = (1 + x) * x / 2
        // rightSum = x + (x+1) + …… + n = (x + n) * (n - x + 1) / 2
        // leftSum == rightSum
        // x = sqrt((n^2 + n)/2)
        int t = n * (n + 1) / 2;
        int x = std::sqrt(t);
        return x * x == t ? x : -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}