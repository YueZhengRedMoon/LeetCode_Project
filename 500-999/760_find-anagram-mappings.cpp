#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> anagramMappings(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        int n = nums1.size();
        std::unordered_map<int, int> indices;
        for (int i = 0; i < n; ++i)
        {
            indices[nums2[i]] = i;
        }
        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            ans[i] = indices[nums1[i]];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
