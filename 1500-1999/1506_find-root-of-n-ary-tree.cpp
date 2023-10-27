#include <iostream>
#include <vector>
#include <unordered_set>

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
    Node* findRoot(std::vector<Node*> tree)
    {
        for (Node *node : tree)
        {
            if (visited.find(node->val) == visited.end())
            {
                dfs(node);
            }
        }

        for (Node *node : tree)
        {
            if (visited.find(node->val) == visited.end())
            {
                return node;
            }
        }

        return nullptr;
    }

private:
    std::unordered_set<int> visited;

    void dfs(Node* node)
    {
        for (Node *child : node->children)
        {
            if (visited.find(child->val) == visited.end())
            {
                visited.insert(child->val);
                dfs(child);
            }
        }
    }
};

class Solution2
{
public:
    Node* findRoot(std::vector<Node*> tree)
    {
        int xorSum = 0;

        for (Node *node : tree)
        {
            xorSum ^= node->val;
            for (Node *child : node->children)
            {
                xorSum ^= child->val;
            }
        }

        for (Node *node : tree)
        {
            if (node->val == xorSum)
            {
                return node;
            }
        }

        return nullptr;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
