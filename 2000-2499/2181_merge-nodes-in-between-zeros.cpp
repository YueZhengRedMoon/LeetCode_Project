#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* mergeNodes(ListNode* head)
    {
        ListNode sentinel;
        ListNode* p = &sentinel, *q = head->next;
        int sum = 0;
        while (q)
        {
            if (q->val == 0)
            {
                p->next = new ListNode(sum);
                sum = 0;
                p = p->next;
            }
            else
            {
                sum += q->val;
            }
            q = q->next;
        }
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
