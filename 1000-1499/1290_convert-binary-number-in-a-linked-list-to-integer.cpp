#include <iostream>
#include "../leetcode.h"

class Solution
{
public:
    int getDecimalValue(ListNode* head)
    {
        int ans = 0;
        ListNode* p = head;
        while (p)
        {
            ans = (ans << 1) + p->val;
            p = p->next;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
