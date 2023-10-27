#include <iostream>
#include <vector>
#include <stack>
#include "../leetcode.h"

class Solution
{
public:
    std::vector<int> nextLargerNodes(ListNode* head)
    {
        std::vector<int> ans(MAX_N);
        std::stack<std::pair<int, int>> stack;  // first:值 second:索引
        ListNode *cur = head;
        int len = 0;
        while (cur)
        {
            while (!stack.empty() && stack.top().first < cur->val)
            {
                std::pair<int, int> top = stack.top();
                stack.pop();
                ans[top.second] = cur->val;
            }
            stack.emplace(cur->val, len++);
            cur = cur->next;
        }
        ans.resize(len);
        return ans;
    }

private:
    const int MAX_N = 10000;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
