#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int closestTarget(std::vector<std::string>& words, std::string target, int startIndex)
    {
        int ans = INT_MAX, n = words.size();
        for (int i = 0; i < n; ++i)
        {
            if (words[i] == target)
            {
                ans = std::min({ans, std::abs(i - startIndex), startIndex + n - i, i + n - startIndex});
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}