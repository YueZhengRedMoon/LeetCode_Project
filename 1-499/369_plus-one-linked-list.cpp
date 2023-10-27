#include <iostream>
#include "../leetcode.h"
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

class Solution2
{
public:
    ListNode* plusOne(ListNode* head)
    {
        ListNode *sentinel = new ListNode(0, head);
        ListNode *notNine = sentinel;

        // 找到最右边的非9节点
        while (head)
        {
            if (head->val != 9)
                notNine = head;
            head = head->next;
        }

        ++notNine->val;
        notNine = notNine->next;
        while (notNine)
        {
            notNine->val = 0;
            notNine = notNine->next;
        }

        return sentinel->val != 0 ? sentinel : sentinel->next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
