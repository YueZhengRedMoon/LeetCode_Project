#include <iostream>
#include <vector>
#include "../leetcode.h"

class Solution
{
public:
    ListNode* removeNodes(ListNode *head)
    {
        std::vector<ListNode*> decStack;
        ListNode *p = head;
        while (p)
        {
            while (!decStack.empty() && decStack.back()->val < p->val)
            {
                decStack.pop_back();
            }
            decStack.push_back(p);
            p = p->next;
        }
        for (int i = 1; i < decStack.size(); ++i)
        {
            decStack[i - 1]->next = decStack[i];
        }
        return decStack[0];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
