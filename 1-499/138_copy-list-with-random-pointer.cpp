#include <iostream>
#include <unordered_map>
#include <vector>

class Node
{
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node* copyRandomList(Node* head)
    {
        std::unordered_map<Node*, Node*> map;
        Node sentinel(0);
        Node *p = head, *pNew = &sentinel;
        while (p)
        {
            pNew->next = new Node(p->val);
            pNew = pNew->next;
            map[p] = pNew;
            p = p->next;
        }
        p = head;
        pNew = sentinel.next;
        while (p)
        {
            if (p->random)
            {
                pNew->random = map[p->random];
            }
            p = p->next;
            pNew = pNew->next;
        }
        return sentinel.next;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
