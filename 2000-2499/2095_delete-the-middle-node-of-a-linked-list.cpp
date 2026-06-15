#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* deleteMiddle(ListNode* head)
    {
        if (head->next == nullptr)
        {
            return nullptr;
        }

        ListNode *p = head, *q = head, *preP = nullptr;
        while (q && q->next)
        {
            q = q->next;
            if (q)
            {
                q = q->next;
            }
            preP = p;
            p = p->next;
        }

        preP->next = p->next;
        return head;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}