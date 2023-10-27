#include <iostream>
#include <deque>
#include "../leetcode.h"

class Solution
{
public:
    void reorderList(ListNode* head)
    {
        std::deque<ListNode *> deque;
        ListNode *p = head->next;
        while (p)
        {
            deque.push_back(p);
            p = p->next;
        }
        p = head;
        while (!deque.empty())
        {
            ListNode *next = deque.back();
            deque.pop_back();
            p->next = next;
            p = next;

            if (!deque.empty())
            {
                next = deque.front();
                deque.pop_front();
                p->next = next;
                p = next;
            }
        }
        p->next = nullptr;
    }
};

class Solution2
{
public:
    void reorderList(ListNode* head)
    {
        if (head->next == nullptr)
            return;

        ListNode *fast = head;
        ListNode *slow = head;
        ListNode *head2 = nullptr;
        while (true)
        {
            if (fast->next)
            {
                fast = fast->next;
            }
            if (fast->next)
            {
                fast = fast->next;
            }
            // 快指针已经遍历完整个链表
            if (fast->next == nullptr)
            {
                // 断开链表
                head2 = slow->next;
                slow->next = nullptr;
                break;
            }
            else
            {
                slow = slow->next;
            }
        }

        head2 = reverseList(head2);

        // len(head2) >= len(head)
        ListNode *p1 = head, *p2 = head2;
        while (p1)
        {
            ListNode *p1Next = p1->next, *p2Next = p2->next;
            p1->next = p2;
            if (p1Next) p2->next = p1Next;
            p1 = p1Next;
            p2 = p2Next;
        }
    }

private:
    ListNode* reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *current = head;
        while (current)
        {
            ListNode *next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}