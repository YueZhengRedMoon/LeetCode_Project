#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == nullptr) return nullptr;

        ListNode sentinel(0, head);
        ListNode *prev = &sentinel, *p = head;
        while (p)
        {
            bool pIsDup = false;
            ListNode *pNext = p->next;
            while (pNext && pNext->val == p->val)
            {
                pNext = pNext->next;
                pIsDup = true;
            }
            if (pIsDup)
            {
                prev->next = pNext;
                p = pNext;
            }
            else
            {
                prev = p;
                p = p->next;
            }
        }
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
