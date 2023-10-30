#include <iostream>
#include <vector>

class Solution
{
public:
    int hIndex(std::vector<int> &citations)
    {
        int n = citations.size(), ans = 0;
        int left = 0, right = n;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (citations[mid] >= n - mid)
            {
                ans = n - mid;
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}