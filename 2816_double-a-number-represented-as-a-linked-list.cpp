#include <iostream>
#include <stack>
#include "leetcode.h"

class Solution
{
public:
    ListNode* doubleIt(ListNode* head)
    {
        std::stack<ListNode*> stack;
        ListNode *p = head;
        while (p)
        {
            stack.push(p);
            p = p->next;
        }
        int carry = 0;
        while (!stack.empty())
        {
            p = stack.top();
            stack.pop();
            p->val += p->val + carry;
            carry = p->val / 10;
            p->val %= 10;
        }
        if (carry)
        {
            ListNode *newHead = new ListNode(carry, head);
            head = newHead;
        }
        return head;
    }
};

class Solution2
{
public:
    ListNode* doubleIt(ListNode* head)
    {
        if (head->val > 4)
        {
            ListNode *newHead = new ListNode(0, head);
            head = newHead;
        }
        for (ListNode *p = head; p; p = p->next)
        {
            p->val *= 2;
            if (p->next && p->next->val > 4)
                ++p->val;
            p->val %= 10;
        }
        return head;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
