#include <iostream>
#include <vector>
#include <queue>

class Node
{
public:
    int val;
    std::vector<Node*> neighbors;

    Node()
    {
        val = 0;
        neighbors = std::vector<Node*>();
    }

    Node(int _val)
    {
        val = _val;
        neighbors = std::vector<Node*>();
    }

    Node(int _val, std::vector<Node*> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node* cloneGraph(Node* node)
    {
        if (node == nullptr) return nullptr;
        std::queue<Node*> queue;
        queue.push(node);
        nodeMap[node->val] = new Node(node->val);
        while (!queue.empty())
        {
            Node *cur = queue.front();
            queue.pop();
            for (Node *neighbor : cur->neighbors)
            {
                if (nodeMap[neighbor->val] == nullptr)
                {
                    nodeMap[neighbor->val] = new Node(neighbor->val);
                    queue.push(neighbor);
                }
                nodeMap[cur->val]->neighbors.push_back(nodeMap[neighbor->val]);
            }
        }
        return nodeMap[node->val];
    }

private:
    Node* nodeMap[101]{nullptr};
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}