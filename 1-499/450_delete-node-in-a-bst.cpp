#include <iostream>

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
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        // 没找到删除的节点，遍历到空节点直接返回
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root->val == key)
        {
            // 左右孩子都为空（叶子节点），直接删除节点，返回nullptr为根节点
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            // 左孩子为空，右孩子不为空，删除root，右孩子补位，返回右孩子为根节点
            else if (root->left == nullptr)
            {
                TreeNode *newRoot = root->right;
                delete root;
                return newRoot;
            }
            // 左孩子不为空，右孩子为空，删除root，左孩子补位，返回左孩子为根节点
            else if (root->right == nullptr)
            {
                TreeNode *newRoot = root->left;
                delete root;
                return newRoot;
            }
            // 左右孩子都不为空，将删除节点的左子树放到删除节点的右子树的最左边，并返回删除节点的右孩子为新的根节点
            else
            {
                // 找到右子树最左边的节点
                TreeNode *current = root->right;
                while (current->left)
                {
                    current = current->left;
                }
                // 将删除节点的左子树放到删除节点的右子树的最左边
                current->left = root->left;
                // 返回删除节点的右孩子为新的根节点
                TreeNode *newRoot = root->right;
                delete root;
                return newRoot;
            }
        } // end of if (root->val == key)

        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }

        if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }

        return root;
    }

    TreeNode* myDeleteNode(TreeNode* root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (key < root->val)
        {
            root->left = myDeleteNode(root->left, key);
        }
        else if (key > root->val)
        {
            root->right = myDeleteNode(root->right, key);
        }
        // 找到要删除的节点
        else
        {
            // 如果有左子树，则找到左子树最大的节点，将root的值替换为左子树的最大值，然后将最大节点删除
            if (root->left)
            {
                TreeNode *newRoot = root->left;
                while (newRoot->right)
                {
                    newRoot = newRoot->right;
                }
                root->val = newRoot->val;
                root->left = myDeleteNode(root->left, root->val);
            }
            // 如果有右子树，则找到右子树最小的节点，将root的值替换为右子树的最小值，然后将最小节点删除
            else if (root->right)
            {
                TreeNode *newRoot = root->right;
                while (newRoot->left)
                {
                    newRoot = newRoot->left;
                }
                root->val = newRoot->val;
                root->right = myDeleteNode(root->right, root->val);
            }
            else
            {
                delete root;
                return nullptr;
            }
        }
        return root;
    }
};

class Solution2
{
public:
    TreeNode* deleteNode(TreeNode *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        TreeNode *current = root;
        TreeNode *pre = nullptr;    // 记录current的父节点，用来删除current
        while (current)
        {
            if (key < current->val)
            {
                pre = current;
                current = current->left;
            }
            else if (key > current->val)
            {
                pre = current;
                current = current->right;
            }
            else
            {
                break;
            }
        }

        if (pre == nullptr)
        {
            return deleteOneNode(current);
        }

        // 没有找到目标节点
        if (current == nullptr)
        {
            return root;
        }

        // 要删除的是左孩子
        if (pre->left == current)
        {
            pre->left = deleteOneNode(current);
        }
        // 要删除的是右孩子
        else
        {
            pre->right = deleteOneNode(current);
        }
        return root;
    }

private:
    /** 将目标节点（删除节点）的左子树放到目标节点右子树最左边的节点的左孩子上，
     *  并返回目标节点的右孩子为新的根节点 */
    TreeNode* deleteOneNode(TreeNode *target)
    {
        if (target == nullptr)
        {
            return nullptr;
        }
        if (target->right == nullptr)
        {
            return target->left;
        }
        TreeNode *current = target->right;
        while (current->left)
        {
            current = current->left;
        }
        current->left = target->left;
        TreeNode *newRoot = target->right;
        delete target;
        return newRoot;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
