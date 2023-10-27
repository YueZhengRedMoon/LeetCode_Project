#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root)
    {
        std::vector<std::vector<int>> sequence;
        levelOrder(root, sequence, 0);
        std::reverse(sequence.begin(), sequence.end());
        return sequence;
    }

private:
    void levelOrder(TreeNode *node, std::vector<std::vector<int>> &sequence, int currentDepth)
    {
        if (node == nullptr)
        {
            return;
        }
        if (currentDepth == sequence.size())
        {
            sequence.push_back(std::vector<int>());
        }
        sequence[currentDepth].push_back(node->val);
        // 遍历下一层
        levelOrder(node->left, sequence, currentDepth + 1);
        levelOrder(node->right, sequence, currentDepth + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
