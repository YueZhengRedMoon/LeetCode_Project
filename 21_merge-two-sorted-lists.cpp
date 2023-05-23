#include <iostream>
#include <vector>
#include "leetcode.h"

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode sentinel;
        ListNode *p1 = list1, *p2 = list2, *cur = &sentinel;
        while (p1 && p2)
        {
            if (p1->val < p2->val)
            {
                cur->next = p1;
                p1 = p1->next;
            }
            else
            {
                cur->next = p2;
                p2 = p2->next;
            }
            cur = cur->next;
        }
        while (p1)
        {
            cur->next = p1;
            p1 = p1->next;
            cur = cur->next;
        }
        while (p2)
        {
            cur->next = p2;
            p2 = p2->next;
            cur = cur->next;
        }
        cur->next = nullptr;
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
