#include <iostream>
#include "leetcode.h"
#include <vector>

class Solution
{
public:
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        if (left == right) return head;
        ListNode *rp = head, *lp = head, *rPrev = nullptr;
        for (int i = 1; i <= right - left; ++i)
            rp = rp->next;
        for (int i = 1; i < left; ++i)
        {
            rPrev = lp;
            lp = lp->next;
            rp = rp->next;
        }
        ListNode *lPrev = rp->next, *end = rp->next;
        while (lp != end)
        {
            ListNode *lNext = lp->next;
            lp->next = lPrev;
            lPrev = lp;
            lp = lNext;
        }
        if (rPrev)
        {
            rPrev->next = lPrev;
        }
        else
        {
            head = lPrev;
        }
        return head;
    }
};

int main()
{
    Solution solution;
    ListNode p5(5);
    ListNode p4(4, &p5);
    ListNode p3(3, &p4);
    ListNode p2(2, &p3);
    ListNode p1(1, &p2);
    ListNode *p = solution.reverseBetween(&p1, 3, 5);
    while (p)
    {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
    return 0;
}
