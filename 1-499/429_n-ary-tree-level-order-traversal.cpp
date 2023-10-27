#include <iostream>
#include <vector>
#include <queue>

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
    std::vector<std::vector<int>> levelOrder(Node* root)
    {
        std::vector<std::vector<int>> levelOrderSequence;
        std::queue<Node *> queue;
        if (root != nullptr)
        {
            queue.push(root);
        }
        while (!queue.empty())
        {
            int numNodeInThisLevel = queue.size();
            levelOrderSequence.push_back(std::vector<int>());
            for (int i = 0; i < numNodeInThisLevel; ++i)
            {
                Node *node = queue.front();
                queue.pop();
                levelOrderSequence.back().push_back(node->val);
                for (auto it = node->children.begin(); it != node->children.end(); ++it)
                {
                    queue.push(*it);
                }
            }
        }
        return levelOrderSequence;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
