#include <iostream>
#include "leetcode.h"

class Solution
{
public:
    ListNode* partition(ListNode* head, int x)
    {
        if (head == nullptr) return nullptr;
        ListNode lessSentinel, geSentinel;
        ListNode *p1 = &lessSentinel, *p2 = &geSentinel, *p = head;
        while (p)
        {
            if (p->val < x)
            {
                p1->next = p;
                p1 = p;
            }
            else
            {
                p2->next = p;
                p2 = p;
            }
            p = p->next;
        }
        p1->next = geSentinel.next;
        p2->next = nullptr;
        return lessSentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
