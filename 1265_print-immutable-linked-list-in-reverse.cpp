#include <iostream>
#include <stack>

class ImmutableListNode
{
public:
    void printValue();              // print the value of the node.
    ImmutableListNode* getNext();   // return the next node.
};

class Solution
{
public:
    void printLinkedListInReverse(ImmutableListNode* head)
    {
        std::stack<ImmutableListNode*> stack;
        ImmutableListNode *p = head;
        while (p)
        {
            stack.push(p);
            p = p->getNext();
        }
        while (!stack.empty())
        {
            p = stack.top();
            stack.pop();
            p->printValue();
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}