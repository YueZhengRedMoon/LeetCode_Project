#include <iostream>
#include <vector>

class Node {
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
    Node* cloneTree(Node* root)
    {
        if (root == nullptr)
            return nullptr;

        Node *newRoot = new Node(root->val);
        newRoot->children.reserve(root->children.size());
        for (Node *child : root->children)
        {
            newRoot->children.push_back(cloneTree(child));
        }
        return newRoot;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
