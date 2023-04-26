#include <iostream>
#include <deque>
#include "leetcode.h"

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

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}