#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head == nullptr) return nullptr;
        ListNode *fast = head;
        int len = 0;
        while (fast)
        {
            ++len;
            fast = fast->next;
        }
        k %= len;
        ListNode *slow = head;
        for (int i = 1; i < len - k; ++i)
        {
            slow = slow->next;
        }
        std::cout << slow->val << std::endl;
        // 先反转从头节点到slow，再反转slow->next到链表尾
        ListNode *head2 = slow->next;
        ListNode *head1 = reverse(head, slow->next);
        head2 = reverse(head2, nullptr);
        head->next = head2; // 原链表头head现在变成了head1的链表尾
        ListNode *newHead = reverse(head1, nullptr);
        return newHead;
    }

private:
    ListNode *reverse(ListNode *head, ListNode *tail)
    {
        ListNode *prev = nullptr, *p = head;
        while (p != tail)
        {
            ListNode *pNext = p->next;
            p->next = prev;
            prev = p;
            p = pNext;
        }
        return prev;
    }
};

class Solution2
{
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head == nullptr) return nullptr;
        int len = 0;
        ListNode *p = head, *prev = nullptr;
        while (p)
        {
            ++len;
            prev = p;
            p = p->next;
        }
        prev->next = head;
        p = head;
        k %= len;
        for (int i = 0; i < len - k; ++i)
        {
            prev = p;
            p = p->next;
        }
        prev->next = nullptr;
        return p;
    }
};

int main()
{
    Solution2 solution;
    ListNode *head = debug::createLinkedList({1, 2, 3, 4, 5});
    ListNode *newHead = solution.rotateRight(head, 2);
    debug::printLinkedList(newHead);
    debug::freeLinkedList(newHead);
    return 0;
}
