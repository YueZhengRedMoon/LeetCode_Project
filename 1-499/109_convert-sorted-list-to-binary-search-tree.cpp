#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        return build(head, nullptr);
    }

private:
    ListNode* getMedian(ListNode* begin, ListNode* end)
    {
        if (begin == end)
            return nullptr;
        if (begin->next == end)
            return begin;

        ListNode *slow = begin, *fast = begin->next->next;
        while (fast != end)
        {
            slow = slow->next;
            fast = fast->next;
            if (fast != end)
                fast = fast->next;
        }
        return slow;
    }

    TreeNode* build(ListNode* begin, ListNode* end)
    {
        ListNode* median = getMedian(begin, end);
        if (median == nullptr)
            return nullptr;
        TreeNode* root = new TreeNode(median->val);
        root->left = build(begin, median);
        root->right = build(median->next, end);
        return root;
    }
};

class Solution2
{
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        int len = getLength(head);
        return buildTree(head, 0, len - 1);
    }

private:
    TreeNode* buildTree(ListNode*& head, int left, int right)
    {
        if (left > right)
            return nullptr;

        int mid = (left + right + 1) / 2;
        TreeNode* root = new TreeNode();
        root->left = buildTree(head, left, mid - 1);
        root->val = head->val;
        head = head->next;
        root->right = buildTree(head, mid + 1, right);
        return root;
    }

    int getLength(ListNode* head)
    {
        int len = 0;
        ListNode* p = head;
        while (p)
        {
            p = p->next;
            ++len;
        }
        return len;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
