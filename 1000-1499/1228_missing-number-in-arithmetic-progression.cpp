#include <iostream>
#include <vector>

class Solution
{
public:
    int missingNumber(std::vector<int> &arr)
    {
        int n = arr.size();
        int d = (arr[n - 1] - arr[0]) / n;
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = (left + right) >> 1;
            if (arr[mid] == arr[0] + mid * d)
            {
                // 如果中间元素所处位置正确，则缺失元素在右半区
                left = mid + 1;
            }
            else
            {
                // 缺失元素在左半区
                right = mid;
            }
        }
        return arr[0] + left * d;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
