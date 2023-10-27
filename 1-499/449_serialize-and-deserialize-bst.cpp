#include <iostream>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <functional>
#include "../leetcode.h"
#include "../debug.h"

constexpr int base = 128;
char itoc[base];
std::unordered_map<char, int> ctoi;
int init =[]{
    char c = 0;
    for (int i = 0; i < base; ++i, ++c)
    {
        itoc[i] = c;
        ctoi[c] = i;
    }
    return 0;
}();

class Codec
{
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root)
    {
        if (root == nullptr)
            return "";

        // 求出二叉搜索树的前序序列
        int count = 0;
        std::ostringstream oss;
        std::stack<TreeNode*> stack;
        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();

            ++count;
            // 将节点值映射为字符串
            oss << encode(node->val);

            if (node->right)
                stack.push(node->right);
            if (node->left)
                stack.push(node->left);
        }
        oss << encode(count);   // 记录节点数

        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data)
    {
        int len = data.size();
        if (len == 0)
            return nullptr;

        // 获取节点数
        int end = len - 2;
        int nodeCount = decode(data, len - 2, len);
        std::vector<int> preorder;
        preorder.reserve(nodeCount);
        for (int i = 2, begin = 0; i <= end; ++i)
        {
            if (i % 2 == 0)
            {
                preorder.push_back(decode(data, begin, i));
                begin = i;
            }
        }

        std::function<TreeNode*(int, int)> build = [&](int begin, int end) -> TreeNode* {
            if (begin > end)
                return nullptr;
            if (begin == end)
                return new TreeNode(preorder[begin]);

            TreeNode *root = new TreeNode(preorder[begin]);
            int mid = end;
            for (int i = begin + 1; i <= end; ++i)
            {
                if (preorder[i] > preorder[begin])
                {
                    mid = i - 1;
                    break;
                }
            }
            root->left = build(begin + 1, mid);
            root->right = build(mid + 1, end);

            return root;
        };

        return build(0, nodeCount - 1);
    }

private:
    std::string encode(int val)
    {
        std::string res(2, 0);
        int i = 0;
        while (val)
        {
            res[i++] = itoc[val % base];
            val /= base;
        }
        return res;
    }

    int decode(const std::string &s)
    {
        int res = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            res += ctoi[s[i]] * pow(base, i);
        }
        return res;
    }

    int decode(const std::string &s, int begin, int end)
    {
        int res = 0;
        for (int i = begin, j = 0; i < end; ++i, ++j)
        {
            res += ctoi[s[i]] * pow(base, j);
        }
        return res;
    }

    int pow(int x, int n)
    {
        int res = 1;
        while (n)
        {
            if (n & 1)
                res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    return 0;
}
