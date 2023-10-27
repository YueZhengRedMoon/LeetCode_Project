#include <iostream>

class Node
{
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val)
    {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next)
    {
        val = _val;
        next = _next;
    }
};

class Solution
{
public:
    Node* insert(Node* head, int insertVal)
    {
        if (head == nullptr)
        {
            head = new Node(insertVal);
            head->next = head;
            return head;
        }

        Node *cur = head, *next = cur->next;
        // 新节点要插入到头节点的前面，向后循环遍历到最小节点
        if (insertVal < head->val)
        {
            while (next->val >= cur->val)
            {
                cur = next;
                next = next->next;

                // 遍历了一圈回到了开始，说明循环链表中所有节点的值都是相同的
                if (cur == head)
                {
                    cur->next = new Node(insertVal, next);
                    return head;
                }
            }
            // 此时next指向最小节点，cur指向最大节点
        }

        // 向后遍历，找到第一个 >= insertVal的节点
        while (next->val < insertVal)
        {
            // cur已经是最大的节点，且新插入节点比cur还大
            if (next->val < cur->val && cur->val < insertVal)
            {
                cur->next = new Node(insertVal, next);
                return head;
            }

            cur = next;
            next = next->next;

            // 遍历了一圈回到了开始，说明循环链表中所有节点的值都是相同的
            if (cur == head)
            {
                cur->next = new Node(insertVal, next);
                return head;
            }
        }

        cur->next = new Node(insertVal, next);
        return head;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
