//
// Created by Kirie on 2023/4/18.
//

#ifndef __LEET_CODE_PROJECT_LEETCODE_H
#define __LEET_CODE_PROJECT_LEETCODE_H
#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace debug
{
    ListNode* createLinkedList(const std::initializer_list<int> &list)
    {
        ListNode sentinel;
        ListNode *p = &sentinel;
        for (int val : list)
        {
            p->next = new ListNode(val);
            p = p->next;
        }
        return sentinel.next;
    }

    void freeLinkedList(ListNode *head)
    {
        while (head)
        {
            ListNode *toDel = head;
            head = head->next;
            delete toDel;
        }
    }

    void printLinkedList(ListNode *head)
    {
        ListNode *p = head;
        while (p)
        {
            std::cout << p->val << ' ';
            p = p->next;
        }
        std::cout << std::endl;
    }
}
#endif //__LEET_CODE_PROJECT_LEETCODE_H
