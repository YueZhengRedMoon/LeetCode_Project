#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr)
    {
        std::sort(arr.begin(), arr.end());
        std::vector<std::vector<int>> ans;
        int minDiff = INT_MAX, n = arr.size();
        for (int i = 1; i < n; ++i)
        {
            int diff = arr[i] - arr[i - 1];
            if (diff < minDiff)
            {
                ans = {{arr[i - 1], arr[i]}};
                minDiff = diff;
            }
            else if (diff == minDiff)
            {
                ans.push_back({arr[i - 1], arr[i]});
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