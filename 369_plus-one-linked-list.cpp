#include <iostream>
#include "leetcode.h"
#include <stack>

class Solution
{
public:
    ListNode* plusOne(ListNode* head)
    {
        std::stack<ListNode*> stack;
        ListNode *p = head;
        while (p)
        {
            stack.push(p);
            p = p->next;
        }
        bool carry = false;
        do
        {
            p = stack.top();
            stack.pop();
            ++p->val;
            if (p->val == 10)
            {
                p->val = 0;
                carry = true;
            }
            else
            {
                carry = false;
            }
        } while (!stack.empty() && carry);

        if (carry)
        {
            ListNode *newHead = new ListNode(1, head);
            head = newHead;
        }

        return head;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
