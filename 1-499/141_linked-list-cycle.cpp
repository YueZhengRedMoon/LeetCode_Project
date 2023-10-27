#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr)
            return false;

        ListNode *slow = head;
        ListNode *fast = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (slow == fast)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}