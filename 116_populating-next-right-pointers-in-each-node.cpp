#include <iostream>
#include <queue>

class Node
{
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    /** 使用已建立的next指针 */
    Node* connect(Node *root)
    {
        Node *leftmost = root;
        while (leftmost)
        {
            Node *head = leftmost;
            leftmost = leftmost->left;
            if (leftmost == nullptr)
            {
                break;
            }
            while (head)
            {
                head->left->next = head->right;

                if (head->next)
                {
                    head->right->next = head->next->left;
                }

                head = head->next;
            }
        }
        return root;
    }

    /** 中序遍历连接next节点 */
    Node* levelOrderConnect(Node* root)
    {
        std::queue<Node *> queue;
        if (root != nullptr)
        {
            queue.push(root);
        }
        while (!queue.empty())
        {
            int numNodeInThisLevel = queue.size();
            for (int i = 0; i < numNodeInThisLevel; ++i)
            {
                Node *node = queue.front();
                queue.pop();

                if (i < numNodeInThisLevel - 1)
                {
                    node->next = queue.front();
                }
                else
                {
                    node->next = nullptr;
                }

                // 完美二叉树，左节点不为空，则右节点必定不空
                if (node->left)
                {
                    queue.push(node->left);
                    queue.push(node->right);
                }
            }
        }
        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
