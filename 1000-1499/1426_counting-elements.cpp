#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int countElements(std::vector<int> &arr)
    {
        std::unordered_set<int> set;
        for (int num : arr)
        {
            set.emplace(num);
        }
        int ans = 0;
        for (int num : arr)
        {
            if (set.find(num + 1) != set.end())
            {
                ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
