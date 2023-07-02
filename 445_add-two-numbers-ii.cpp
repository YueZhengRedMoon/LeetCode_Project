#include <iostream>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        std::stack<int> stack1, stack2;
        ListNode *p;
        p = l1;
        while (p)
        {
            stack1.push(p->val);
            p = p->next;
        }
        p = l2;
        while (p)
        {
            stack2.push(p->val);
            p = p->next;
        }
        if (stack1.size() < stack2.size())
        {
            std::swap(stack1, stack2);
        }

        p = nullptr;
        int carry = 0;
        while (!stack2.empty())
        {
            int val1 = stack1.top();
            stack1.pop();
            int val2 = stack2.top();
            stack2.pop();

            int val = val1 + val2 + carry;
            carry = val / 10;
            val %= 10;

            ListNode *newP = new ListNode(val, p);
            p = newP;
        }

        while (!stack1.empty())
        {
            int val = stack1.top();
            stack1.pop();

            val += carry;
            carry = val / 10;
            val %= 10;

            ListNode *newP = new ListNode(val, p);
            p = newP;
        }

        if (carry)
        {
            ListNode *newP = new ListNode(carry, p);
            p = newP;
        }

        return p;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}