#include <iostream>
#include <vector>
#include <unordered_map>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    struct Node
    {
        TreeNode *treeNode{nullptr};
        unsigned int inorderIndex{0};        // 该节点在中序序列中的索引
    };

    TreeNode* buildTree(std::vector<int> &preorder, std::vector<int> &inorder)
    {
        // 建立节点值到节点和其索引的映射
        for (unsigned int i = 0; i < inorder.size(); ++i)
        {
            unorderedMap[inorder[i]] = {new TreeNode(inorder[i]), i};
        }

        return buildTree(preorder, inorder, 0, inorder.size() - 1, 0);
    }

private:
    /** 节点值到节点和其索引的映射 */
    std::unordered_map<int, Node> unorderedMap;

    TreeNode* buildTree(std::vector<int> &preorder, std::vector<int> &inorder,
                        int begin, int end, int rootIndex)
    {
        if (rootIndex >= preorder.size() || begin > end)
        {
            return nullptr;
        }

        if (begin == end)
        {
            return unorderedMap[inorder[begin]].treeNode;
        }

        Node value = unorderedMap[preorder[rootIndex]];
        TreeNode *root = value.treeNode;
        int inorderIndex = value.inorderIndex;

        root->left = buildTree(preorder, inorder, begin, inorderIndex - 1, rootIndex + 1);
        root->right = buildTree(preorder, inorder, inorderIndex + 1, end,
                                rootIndex + (inorderIndex - begin) + 1);

        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
