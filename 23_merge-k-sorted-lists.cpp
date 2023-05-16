#include <iostream>
#include <vector>
#include <queue>
#include "leetcode.h"

class Solution
{
public:
    struct Greater
    {
        bool operator()(ListNode* const& lhs, ListNode *const& rhs)
        {
            return lhs->val > rhs->val;
        }
    };

    ListNode* mergeKLists(std::vector<ListNode*> &lists)
    {
        std::priority_queue<ListNode*, std::vector<ListNode*>, Greater> minHeap;
        for (const auto &node : lists)
        {
            if (node != nullptr)
            {
                minHeap.push(node);
            }
        }

        ListNode sentinel;
        ListNode *cur = &sentinel;
        while (!minHeap.empty())
        {
            ListNode *top = minHeap.top();
            minHeap.pop();
            cur->next = top;
            cur = top;
            if (top->next)
            {
                minHeap.push(top->next);
            }
        }
        cur->next = nullptr;
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}