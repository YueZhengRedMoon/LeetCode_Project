#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* deleteNodes(ListNode* head, int m, int n)
    {
        if (head == nullptr)
            return nullptr;

        ListNode *p = head;
        for (int i = 1; i < m && p; ++i)
        {
            p = p->next;
        }
        if (p == nullptr)
            return head;
        ListNode *q = p->next;
        for (int i = 0; i < n && q; ++i)
        {
            q = q->next;
        }
        p->next = q;
        deleteNodes(q, m, n);
        return head;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
