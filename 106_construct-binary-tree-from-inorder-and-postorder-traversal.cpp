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

    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder)
    {
        // 节点值都是唯一的，所以构建节点值与节点的映射关系
        for (unsigned int i = 0; i < inorder.size(); ++i)
        {
            unorderedMap[inorder[i]] = {new TreeNode(inorder[i]), i};
        }

        return buildTree(inorder, postorder, 0, inorder.size() - 1, postorder.size() - 1);
    }

private:
    std::unordered_map<int, Node> unorderedMap;

    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder,
                        int begin, int end, int rootIndex)
    {
        if (rootIndex < 0 || begin > end)
        {
            return nullptr;
        }

        if (begin == end)
        {
            return unorderedMap[inorder[begin]].treeNode;
        }

        Node value = unorderedMap[postorder[rootIndex]];
        TreeNode *root = value.treeNode;
        int inorderIndex = value.inorderIndex;  // 根节点在中序序列中的序号
        // 左子树的范围：begin ~ inorderIndex - 1
        root->left = buildTree(inorder, postorder, begin, inorderIndex - 1,
                               rootIndex - (end - inorderIndex) - 1);
        // 右子树的范围：inorderIndex + 1 ~ end
        root->right = buildTree(inorder, postorder, inorderIndex + 1, end,
                                rootIndex - 1);
        return root;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
