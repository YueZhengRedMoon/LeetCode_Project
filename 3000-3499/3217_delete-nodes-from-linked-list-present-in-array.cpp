#include <iostream>
#include <vector>
#include <unordered_set>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* modifiedList(std::vector<int>& nums, ListNode* head)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        ListNode sentinel(0, head);
        ListNode* pre = &sentinel, *p = head;
        while (p)
        {
            if (set.find(p->val) != set.end())
            {
                p = p->next;
                pre->next = p;
            }
            else
            {
                pre = p;
                p = p->next;
            }
        }
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}