#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    std::vector<int> nextGreaterElements(std::vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return {-1};
        }

        int numsSize = nums.size();
        std::vector<int> ans(numsSize, -1);
        std::vector<bool> used(numsSize, false);
        std::stack<int> stack;
        stack.push(0);
        for (int i = 1; !stack.empty() && stack.top() != i; i = (i + 1) % numsSize)
        {
            while (!stack.empty() && nums[stack.top()] < nums[i])
            {
                int topIndex = stack.top();
                stack.pop();
                ans[topIndex] = nums[i];
            }
            if (!used[i])
            {
                stack.push(i);
                used[i] = true;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> nextGreaterElements(std::vector<int> &nums)
    {
        int size = nums.size();
        std::vector<int> ans(size, -1);
        std::stack<int> stack;
        for (int i = 0; i < 2 * size; ++i)
        {
            int index = i % size;
            while (!stack.empty() && nums[stack.top()] < nums[index])
            {
                ans[stack.top()] = nums[index];
                stack.pop();
            }
            stack.push(index);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}