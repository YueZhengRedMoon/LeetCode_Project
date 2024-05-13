#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* nextGroupFirst = head;
        bool reverseNextGroup = true;   // 是否翻转下一组
        for (int i = 0; i < k ; ++i)
        {
            if (nextGroupFirst)
                nextGroupFirst = nextGroupFirst->next;
            else
            {
                // 下一组不足k个元素，不翻转
                reverseNextGroup = false;
                break;
            }
        }
        if (!reverseNextGroup)
            return head;

        ListNode sentinel;
        ListNode *cur = head, *prev = nullptr, *end = nextGroupFirst, *prevGroupLast = &sentinel, *next, *curGroupLast;
        while (true)
        {
            curGroupLast = cur;
            while (cur != end)
            {
                next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
                if (nextGroupFirst)
                    nextGroupFirst = nextGroupFirst->next;
                else
                    reverseNextGroup = false;
            }

            prevGroupLast->next = prev;
            prevGroupLast = curGroupLast;
            if (!reverseNextGroup)
            {
                curGroupLast->next = end;
                break;
            }
            end = nextGroupFirst;
            prev = nullptr;
        }

        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
