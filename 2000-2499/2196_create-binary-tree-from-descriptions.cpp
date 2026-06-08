#include <iostream>
#include <vector>
#include <unordered_map>
#include "../leetcode.h"

class Solution
{
public:
    TreeNode* createBinaryTree(std::vector<std::vector<int>>& descriptions)
    {
        std::unordered_map<int, TreeNode*> nodes;
        nodes.reserve(descriptions.size() + 1); // descriptions中存储了n条边，即有n+1个节点
        int root = 0;   // 把树上每个值异或一遍，再把所有child异或一遍。由于同一个值异或两次等于 0，所以最终异或和恰好等于根节点的值。
        for (const std::vector<int>& d : descriptions)
        {
            int parentVal = d[0], childVal = d[1], isLeft = d[2];

            TreeNode* parent = nodes[parentVal];
            if (parent == nullptr)
            {
                parent = new TreeNode(parentVal);
                nodes[parentVal] = parent;
                root ^= parentVal;
            }
            TreeNode* child = nodes[childVal];
            if (child == nullptr)
            {
                child = new TreeNode(childVal);
                nodes[childVal] = child;
                root ^= childVal;
            }

            if (isLeft)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
            root ^= childVal;
        }
        return nodes[root];
    }
};

class MySolution
{
public:
    TreeNode* createBinaryTree(std::vector<std::vector<int>>& descriptions)
    {
        // map[x].first:x的TreeNode指针
        // map[x].second:x的父节点
        std::unordered_map<int, std::pair<TreeNode*, TreeNode*>> map;
        for (const std::vector<int>& d : descriptions)
        {
            int parentVal = d[0], childVal = d[1], isLeft = d[2];
            std::pair<TreeNode*, TreeNode*>& parentPair = map[parentVal];
            std::pair<TreeNode*, TreeNode*>& childPair = map[childVal];

            if (parentPair.first == nullptr)
            {
                parentPair.first = new TreeNode(parentVal);
            }
            if (childPair.first == nullptr)
            {
                childPair.first = new TreeNode(childVal);
            }

            childPair.second = parentPair.first;
            if (isLeft)
            {
                parentPair.first->left = childPair.first;
            }
            else
            {
                parentPair.first->right = childPair.first;
            }
        }

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            const std::pair<TreeNode*, TreeNode*>& pair = it->second;
            if (pair.second == nullptr)
            {
                return pair.first;
            }
        }
        return nullptr;
    }
};



int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}