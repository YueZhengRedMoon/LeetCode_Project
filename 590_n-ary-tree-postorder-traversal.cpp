#include <iostream>
#include <vector>
#include <stack>

class Node
{
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

class Solution
{
public:
    std::vector<int> postorder(Node* root)
    {
        std::vector<int> postorderSequence;
        std::stack<Node*> stack;
        if (root != nullptr)
        {
            stack.push(root);
        }
        while (!stack.empty())
        {
            Node *node = stack.top();
            stack.pop();

            if (node)
            {
                stack.push(node);
                stack.push(nullptr);

                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it)
                {
                    stack.push(*it);
                }
            }
            else
            {
                node = stack.top();
                stack.pop();
                postorderSequence.push_back(node->val);
            }
        }
        return postorderSequence;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
