#include <iostream>
#include <vector>
#include <unordered_map>
#include "leetcode.h"

class Solution
{
public:
    ListNode* removeZeroSumSublists(ListNode* head)
    {
        ListNode sentinel;
        std::vector<std::pair<int, ListNode*>> stack(1001);
        int top = 0;
        stack[0].second = &sentinel;
        ListNode *p = head;
        while (p)
        {
            if (p->val == 0)
            {
                p = p->next;
                continue;
            }
            if (top > 0)
            {
                int sum = p->val;
                bool deleted = false;
                for (int i = top; i > 0; --i)
                {
                    sum += stack[i].first;
                    if (sum == 0)
                    {
                        top = i - 1;
                        deleted = true;
                        break;
                    }
                }
                if (deleted)
                {
                    p = p->next;
                    continue;
                }
            }
            ++top;
            stack[top].first = p->val;
            stack[top].second = p;
            p = p->next;
        }
        p = stack[0].second;
        for (int i = 1; i <= top; ++i)
        {
            p->next = stack[i].second;
            p = p->next;
        }
        p->next = nullptr;
        return sentinel.next;
    }
};

class Solution2
{
public:
    ListNode* removeZeroSumSublists(ListNode* head)
    {
        ListNode sentinel(0, head);
        std::unordered_map<int, ListNode*> seen;
        int prefix = 0;
        for (ListNode *p = &sentinel; p; p = p->next)
        {
            prefix += p->val;
            seen[prefix] = p;
        }
        prefix = 0;
        for (ListNode *p = &sentinel; p; p = p->next)
        {
            prefix += p->val;
            p->next = seen[prefix]->next;
        }
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}