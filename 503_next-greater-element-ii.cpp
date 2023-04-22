#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> nextGreaterElements(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        std::vector<int> ans(numsSize, -1);
        std::stack<int> stack;
        stack.push(0);
        for (int i = 1; !stack.empty() && stack.top() != i; i = (i + 1) % numsSize)
        {
            while (!stack.empty() && nums[stack.top()] < nums[i])
            {
                int topIndex = stack.top();
                stack.pop();
                ans[topIndex] = i;
            }
            stack.push(i);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}