#include <iostream>
#include "..\leetcode.h"

class Solution
{
public:
    ListNode* insertGreatestCommonDivisors(ListNode *head)
    {
        ListNode *p = head;
        while (p)
        {
            ListNode *next = p->next;
            if (next)
            {
                ListNode *newNode = new ListNode(gcd(p->val, next->val), next);
                p->next = newNode;
            }
            p = next;
        }
        return head;
    }

private:
    int gcd(int a, int b)
    {
        while (b)
        {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
