#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <limits>

class Solution
{
public:
    bool verifyPreorder(std::vector<int> &preorder)
    {
        std::vector<int> inorder(preorder);
        std::sort(inorder.begin(), inorder.end());

        return canBuildBST(preorder, inorder, preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

private:
    bool canBuildBST(std::vector<int> &preorder, std::vector<int> &inorder,
                     std::vector<int>::iterator preBegin, std::vector<int>::iterator preEnd,
                     std::vector<int>::iterator inBegin, std::vector<int>::iterator inEnd)
    {
        if (preBegin == preEnd)
            return false;

        // 根节点的值
        int root = *preBegin;
        // 根节点在中序序列中的迭代器
        std::vector<int>::iterator it = std::lower_bound(inBegin, inEnd, root);
        if (it == inEnd || *it != root)
        {
            // 在中序序列中没有找到对应的根节点
            return false;
        }

        int leftTreeSize = it - inBegin, rightTreeSize = inEnd - it - 1;

        if (leftTreeSize > 0)
        {
            bool leftIsBST = canBuildBST(preorder, inorder, preBegin + 1, preBegin + 1 + leftTreeSize, inBegin, it);
            if (!leftIsBST)
                return false;
        }

        if (rightTreeSize > 0)
        {
            bool rightIsBST = canBuildBST(preorder, inorder, preBegin + 1 + leftTreeSize, preEnd, it + 1, inEnd);
            if (!rightIsBST)
                return false;
        }

        return true;
    }
};

class Solution2
{
public:
    bool verifyPreorder(std::vector<int> &preorder)
    {
        std::stack<int> stack;
        int newMin = std::numeric_limits<int>::min();
        for (int val : preorder)
        {
            if (val < newMin)
                return false;
            while (!stack.empty() && val > stack.top())
            {
                newMin = stack.top();
                stack.pop();
            }
            stack.push(val);
        }
        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<int> preorder = {5, 2, 1, 3, 6};
    bool ans = solution.verifyPreorder(preorder);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
