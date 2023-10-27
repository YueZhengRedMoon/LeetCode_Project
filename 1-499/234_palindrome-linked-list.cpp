#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    bool isPalindrome(ListNode* head)
    {
        if (head->next == nullptr)
        {
            return true;
        }

        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *prev = nullptr;
        ListNode *head1 = nullptr;
        ListNode *head2 = nullptr;
        int i = 0;
        while (fast)
        {
            if (fast->next)
            {
                fast = fast->next;
                ++i;
            }
            if (fast->next)
            {
                fast = fast->next;
                ++i;
            }
            if (fast->next == nullptr)
            {
                // 链表中的节点数是奇数
                if (i % 2 == 0)
                {
                    ListNode* next = slow->next;
                    head2 = new ListNode(next->val, next->next);
                    slow->next = prev;
                    next->next = slow;
                    head1 = next;
                }
                // 链表中的节点数是偶数
                else
                {
                    head1 = slow;
                    head2 = slow->next;
                    head1->next = prev;
                }
                break;
            }
            else
            {
                ListNode *next = slow->next;
                slow->next = prev;
                prev = slow;
                slow = next;
            }

        }

        while (head1 && head2)
        {
            if (head1->val != head2->val)
            {
                return false;
            }
            head1 = head1->next;
            head2 = head2->next;
        }

        return true;
    }
};

int main()
{

    return 0;
}