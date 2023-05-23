#include <iostream>
#include <vector>
#include "leetcode.h"

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode *p1 = l1, *p2 = l2, *prev;
        int carry = 0;
        while (p1 && p2)
        {
            int res = p1->val + p2->val + carry;
            if (res >= 10)
            {
                carry = res / 10;
                res %= 10;
            }
            else
            {
                carry = 0;
            }
            p1->val = res;
            prev = p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        if (p1)
        {
            while (p1 && carry)
            {
                p1->val += carry;
                if (p1->val >= 10)
                {
                    carry = p1->val / 10;
                    p1->val %= 10;
                }
                else
                {
                    carry = 0;
                }
                prev = p1;
                p1 = p1->next;
            }
            if (carry)
            {
                prev->next = new ListNode(carry);
            }
        }
        else if (p2)
        {
            prev->next = p2;
            p1 = p2;
            while (p1 && carry)
            {
                p1->val += carry;
                if (p1->val >= 10)
                {
                    carry = p1->val / 10;
                    p1->val %= 10;
                }
                else
                {
                    carry = 0;
                }
                prev = p1;
                p1 = p1->next;
            }
            if (carry)
            {
                prev->next = new ListNode(carry);
            }
        }
        else if (carry)
        {
            prev->next = new ListNode(carry);
        }
        return l1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
