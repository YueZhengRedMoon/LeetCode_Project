#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        ListNode *p = head;
        while (p)
        {
            ListNode *q = p->next;
            while (q && q->val == p->val)
            {
                q = q->next;
            }
            p->next = q;
            p = q;
        }
        return head;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
