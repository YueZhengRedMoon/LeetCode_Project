#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    std::vector<int> findIntersectionValues(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_set<int> set1(nums1.begin(), nums1.end()), set2(nums2.begin(), nums2.end());
        int ans1 = std::count_if(nums1.begin(), nums1.end(), [&set2](int x) {return set2.find(x) != set2.end();});
        int ans2 = std::count_if(nums2.begin(), nums2.end(), [&set1](int x) {return set1.find(x) != set1.end();});
        return {ans1, ans2};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
