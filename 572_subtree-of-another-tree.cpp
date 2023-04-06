#include <iostream>
#include <stack>
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
    /** 获取两棵树的含空孩子的前序序列，使用KMP算法判断子树的前序序列是否是树的前序序列的子串 */
    bool isSubtreeKMP(TreeNode* root, TreeNode* subRoot)
    {
        // 获取两棵树的前序序列
        std::vector<int> rootPostorderSequence;
        std::vector<int> subRootPostorderSequence;
        getInorderSequence(root, rootPostorderSequence);
        getInorderSequence(subRoot, subRootPostorderSequence);

        // KMP算法判断subRootPostorderSequence是否是rootPostorderSequence的子串
        return KMP(rootPostorderSequence, subRootPostorderSequence);
    }

    /** 暴力解法，前序遍历+递归 */
    bool isSubtreePostorderRecursive(TreeNode* root, TreeNode* subRoot)
    {
        std::stack<TreeNode *>stack;
        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();

            if (node->val == subRoot->val && isSameTree(node, subRoot))
            {
                return true;
            }

            if (node->right) stack.push(node->right);
            if (node->left) stack.push(node->left);
        }
        return false;
    }
private:
    const int lNull = -20000;
    const int rNull = 20000;

    /** 获取root的前序序列，其中如果左孩子为空，则补上lNull，如果右孩子为空，则补上rNull。
     *  实际上不区分lNull和rNull也可以 */
    void getPostorderSequence(TreeNode *root, std::vector<int> &postorderSequence)
    {
        TreeNode leftNull(lNull);
        TreeNode rightNull(rNull);

        std::stack<TreeNode *> stack;
        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();

            postorderSequence.push_back(node->val);

            if (node == &leftNull || node == &rightNull) continue;

            stack.push(node->right ? node->right : &rightNull);
            stack.push(node->left ? node->left : &leftNull);
        }
    }

    void getInorderSequence(TreeNode *root, std::vector<int> &inorderSequence)
    {
//        TreeNode nullNode(lNull);
//
//        std::stack<TreeNode *> stack;
//        TreeNode *current = root;
//        while (current || !stack.empty())
//        {
//            if (current)
//            {
//                stack.push(current);
//                current = current->left;
//            }
//            else
//            {
//                inorderSequence.push_back(nullNode.val);
//                current = stack.top();
//                stack.pop();
//                inorderSequence.push_back(current->val);
//                current = current->right;
//            }
//        }
        TreeNode leftNull(lNull);
        TreeNode rightNull(rNull);
        std::stack<TreeNode *> stack;
        if (root != nullptr)
        {
            stack.push(root);
        }
        while (!stack.empty())
        {
            TreeNode *node = stack.top();
            stack.pop();

            if (node == &leftNull || node == &rightNull)
            {
                inorderSequence.push_back(node->val);
                continue;
            }

            if (node)
            {
                if (node->right) stack.push(node->right);
                else stack.push(&rightNull);

                stack.push(node);
                stack.push(nullptr);

                if (node->left) stack.push(node->left);
                else stack.push(&leftNull);
            }
            else
            {
                node = stack.top();
                stack.pop();
                inorderSequence.push_back(node->val);
            }
        }
    }

    bool KMP(std::vector<int> &s, std::vector<int> &t)
    {
        int sSize = s.size();
        int tSize = t.size();

        int *next = new int[tSize];
        getNext(next, t);

        int j = -1;
        for (int i = 0; i < sSize; ++i)
        {
            while (j >= 0 && s[i] != t[j + 1])
            {
                j = next[j];
            }
            if (s[i] == t[j + 1])
            {
                ++j;
            }
            if (j == tSize - 1)
            {
                delete [] next;
                return true;
            }
        }

        delete [] next;
        return false;
    }

    void getNext(int *next, std::vector<int> &t)
    {
        // i:后缀的尾部
        // j + 1:前缀的尾部，同时也是最长相等前后缀的长度
        // next[i]:t[0:i]的最长相等前后缀的长度-1
        int tSize = t.size();
        int j = -1;
        next[0] = j;
        for (int i = 1; i < tSize; ++i)
        {
            // 前后缀尾部不相同
            while (j >= 0 && t[i] != t[j + 1])
            {
                j = next[j];    // 回退j
            }
            // 前后缀尾部相同
            if (t[i] == t[j + 1])
            {
                ++j;    // 最长相等前后缀的长度 + 1
            }
            // 记录t[0:i]的最长相等前后缀的长度
            next[i] = j;
        }
    }

    /** 判断p和q是否是相同的树 */
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if (p == nullptr && q != nullptr) return false;
        else if (p != nullptr && q == nullptr) return false;
        else if (p == nullptr && q == nullptr) return true;
        else if (p->val != q->val) return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

/** 树哈希 */
class TreeHash
{
public:
    struct Status
    {
        int f;  // 哈希值
        int s;  // 子树大小
        Status(int f_ = 0, int s_ = 0) : f(f_), s(s_) {}
    };

    bool isSubtree(TreeNode *s, TreeNode *t)
    {
        getPrime();
        dfs(s, hS);
        dfs(t, hT);

        int tHash = hT[t].f;
        for (const auto &[k, v] : hS)
        {
            if (v.f == tHash)
            {
                return true;
            }
        }

        return false;
    }

private:
    static constexpr int MAX_N = 1000 + 5;
    static constexpr int MOD = int(1e9) + 7;
    bool visit[MAX_N];
    int prime[MAX_N];
    int numPrime;
    std::unordered_map<TreeNode *, Status> hS, hT;

    void dfs(TreeNode *node, std::unordered_map<TreeNode *, Status> &h)
    {
        h[node] = Status(node->val, 1);
        if (node->left == nullptr && node->right == nullptr)
        {
            return;
        }

        if (node->left)
        {
            dfs(node->left, h);
            h[node].s += h[node->left].s;
            h[node].f = (h[node].f + (179LL * h[node->right].f * prime[h[node->right].s]) % MOD) % MOD;
        }

        if (node->right)
        {
            dfs(node->right, h);
            h[node].s += h[node->right].s;
            h[node].f = (h[node].f + (179LL * h[node->right].f * prime[h[node->right].s]) % MOD) % MOD;
        }
    }

    /** 获取素数 */
    void getPrime()
    {
        visit[0] = visit[1] = true;
        numPrime = 0;
        for (int i = 2; i < MAX_N; ++i)
        {
            if (!visit[i])
            {
                prime[++numPrime] = i;
            }
            for (int j = 1; j <= numPrime && (i * prime[j] < MAX_N); ++j)
            {
                visit[i * prime[j]] = true;
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
