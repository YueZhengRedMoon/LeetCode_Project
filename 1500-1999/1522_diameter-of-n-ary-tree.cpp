#include <iostream>
#include <vector>

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
    int diameter(Node* root)
    {
         ans = 0;
         int depth = maxDepth(root);
         if (depth - 1 > ans)
         {
             ans = depth - 1;
         }
        return ans;
    }

private:
    int ans;

    int maxDepth(Node *node)
    {
        int depth1st = 0, depth2nd = 0;

        for (Node *child : node->children)
        {
            int childDepth = maxDepth(child);
            if (childDepth >= depth1st)
            {
                depth2nd = depth1st;
                depth1st = childDepth;
            }
            else if (childDepth > depth2nd)
            {
                depth2nd = childDepth;
            }
            ans = std::max(ans, depth1st + depth2nd);
        }
        return 1 + depth1st;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}