#include <iostream>

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
    Node* connect(Node *root)
    {
        Node *leftmost = root;
        while (leftmost)
        {
            Node *currentNode = leftmost;
            leftmost = nullptr;
            while (currentNode)
            {
                // 左子节点的next
                if (currentNode->left)
                {
                    if (leftmost == nullptr) leftmost = currentNode->left;

                    if (currentNode->right)
                    {
                        currentNode->left->next = currentNode->right;
                    }
                    else
                    {
                        Node *next = currentNode->next;
                        while (next)
                        {
                            if (next->left)
                            {
                                currentNode->left->next = next->left;
                                break;
                            }
                            else if (next->right)
                            {
                                currentNode->left->next =next->right;
                                break;
                            }
                            else
                            {
                                next = next->next;
                            }
                        }
                    }
                }

                // 右子节点的next
                if (currentNode->right)
                {
                    if (leftmost == nullptr) leftmost = currentNode->right;

                    Node *next = currentNode->next;
                    while (next)
                    {
                        if (next->left)
                        {
                            currentNode->right->next = next->left;
                            break;
                        }
                        else if (next->right)
                        {
                            currentNode->right->next = next->right;
                            break;
                        }
                        else
                        {
                            next = next->next;
                        }
                    }
                }

                currentNode = currentNode->next;
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
