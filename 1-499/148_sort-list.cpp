#include <iostream>
#include "../leetcode.h"

/** 递归实现自顶向下的归并排序，时间复杂度O(nlogn)，空间复杂度O(logn) */
class Solution
{
public:
    ListNode* sortList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        ListNode *head1 = head;
        ListNode *head2 = getMiddleNode(head);
        head1 = sortList(head1);
        head2 = sortList(head2);
        return merge(head1, head2);
    }

private:
    /** 将链表从中间分为两半，返回另一半的头节点 */
    ListNode* getMiddleNode(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode *head2 = slow->next;
        slow->next = nullptr;
        return head2;
    }

    /** 合并两个升序的链表 */
    ListNode* merge(ListNode *head1, ListNode *head2)
    {
        ListNode sentinel;
        ListNode *prev = &sentinel, *p = head1, *q = head2;
        while (p && q)
        {
            if (p->val < q->val)
            {
                prev->next = p;
                prev = p;
                p = p->next;
            }
            else
            {
                prev->next = q;
                prev = q;
                q = q->next;
            }
        }
        if (p)
        {
            prev->next = p;
        }
        if (q)
        {
            prev->next = q;
        }
        return sentinel.next;
    }
};

/** 自底向上的归并排序，时间复杂度O(nlogn)，空间复杂度O(1) */
class Solution2
{
public:
    ListNode* sortList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr) return head;
        int len = 0;
        ListNode *p = head;
        while (p)
        {
            p = p->next;
            ++len;
        }

        ListNode sentinel(0, head);
        for (int subLen = 1; subLen < len; subLen <<= 1)
        {
            ListNode *prev = &sentinel, *cur = sentinel.next;
            while (cur)
            {
                // 挑选出长度为subLen的两个子链表head1与head2
                ListNode *head1= cur;
                for (int i = 1; i < subLen && cur->next; ++i)
                {
                    cur = cur->next;
                }
                ListNode *head2 = cur->next;
                cur->next = nullptr;
                cur = head2;
                for (int i = 1; i < subLen && cur && cur->next; ++i)
                {
                    cur = cur->next;
                }
                // 记录下一段的第一个节点
                ListNode *next = nullptr;
                if (cur)
                {
                    next = cur->next;
                    cur->next = nullptr;
                }
                // 合并head1与head2
                ListNode *merged = merge(head1, head2);
                // 将合并后的链表接在已排序的部分上
                prev->next = merged;
                // 遍历到已排序部分的最后一个节点
                while (prev->next)
                {
                    prev = prev->next;
                }
                // 处理下一段未排序的链表
                cur = next;
            }
        }

        return sentinel.next;
    }

private:
    /** 合并两个升序的链表 */
    ListNode* merge(ListNode *head1, ListNode *head2)
    {
        ListNode sentinel;
        ListNode *prev = &sentinel, *p = head1, *q = head2;
        while (p && q)
        {
            if (p->val < q->val)
            {
                prev->next = p;
                prev = p;
                p = p->next;
            }
            else
            {
                prev->next = q;
                prev = q;
                q = q->next;
            }
        }
        if (p)
        {
            prev->next = p;
        }
        if (q)
        {
            prev->next = q;
        }
        return sentinel.next;
    }
};

int main()
{
    Solution solution;
    ListNode *head = debug::createLinkedList({4, 2, 1, 3});
    head = solution.sortList(head);
    debug::printLinkedList(head);
    debug::freeLinkedList(head);
    return 0;
}
