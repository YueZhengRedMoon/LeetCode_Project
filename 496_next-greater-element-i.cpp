#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> nextGreaterElement(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        std::unordered_map<int, int> indices;
        for (int i = 0; i < nums1.size(); ++i)
        {
            indices[nums1[i]] = i;
        }

        std::vector<int> ans(nums1.size(), -1);
        std::stack<int> stack;
        for (int i = 0; i < nums2.size(); ++i)
        {
            while (!stack.empty() && stack.top() < nums2[i])
            {
                int num = stack.top();
                stack.pop();
                // num右边第一个比num大的数是nums2[i]
                if (indices.find(num) != indices.end())
                {
                    ans[indices[num]] = nums2[i];
                }
            }
            stack.push(nums2[i]);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}