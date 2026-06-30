#include <iostream>
#include <vector>
#include <memory>
#include <string_view>
#include <queue>

constexpr int MAX_ALPHA = 26;

struct Node
{
    std::shared_ptr<Node> children[MAX_ALPHA];
    std::shared_ptr<Node> fail; // 当 node.children[i] 失配时，node.fail.children[i] 即为下一个待匹配节点（等于 root 则表示没有匹配）
    std::shared_ptr<Node> last; // 后缀链接（suffix link），用来快速跳到一定是某个模式串末尾的节点（等于 root 则表示匹配结束）
    int cnt = 0;    // 该节点是cnt个模式串的末尾
};

class AhoCorasick
{
public:
    AhoCorasick() : root(std::make_shared<Node>()) {}

    // 把模式串 pattern 插入 AC 自动机
    void put(std::string_view pattern)
    {
        std::shared_ptr<Node> cur = root;
        for (char c : pattern)
        {
            int idx = c - 'a';
            if (cur->children[idx] == nullptr)
            {
                cur->children[idx] = std::make_shared<Node>();
            }
            cur = cur->children[idx];
        }
        ++cur->cnt;
    }

    // BFS，构建 AC 自动机的 fail 和 last，方便快速查询
    void buildFail()
    {
        root->fail = root->last = root;

        std::queue<std::shared_ptr<Node>> q;
        for (std::shared_ptr<Node>& child : root->children)
        {
            if (child == nullptr)
            {
                child = root;
                continue;
            }
            child->fail = child->last = root;   // 第一层的 fail 都指向根节点
            q.push(child);
        }

        // BFS
        while (!q.empty())
        {
            std::shared_ptr<Node> cur = q.front();
            q.pop();
            for (int i = 0; i < MAX_ALPHA; ++i)
            {
                std::shared_ptr<Node>& child = cur->children[i];
                if (child == nullptr)
                {
                    // 把虚拟子节点 cur.children[i] 设置为 cur.fail.children[i]
                    // 方便失配时直接跳到下一个可能匹配的位置（但不一定是某个模式串的末尾）
                    child = cur->fail->children[i];
                    continue;
                }
                child->fail = cur->fail->children[i];   // 计算失配位置
                // 沿着 last 往上走，可以直接跳到一定是某个模式串末尾的节点（如果跳到 root 表示匹配结束）
                child->last = child->fail->cnt ? child->fail : child->fail->last;
                q.push(child);
            }
        }
    }

    std::shared_ptr<Node> getRoot()
    {
        return root;
    }

private:
    std::shared_ptr<Node> root;
};

class Solution
{
public:
    int numOfStrings(std::vector<std::string>& patterns, std::string word)
    {
        AhoCorasick ac;
        for (std::string_view pattern : patterns)
        {
            ac.put(pattern);
        }
        ac.buildFail();

        std::shared_ptr<Node> cur = ac.getRoot();
        int ans = 0;
        for (char c : word)
        {
            cur = cur->children[c - 'a'];
            for (std::shared_ptr<Node> match = cur; match->cnt >= 0; match = match->last)
            {
                ans += match->cnt;
                match->cnt = -1;    // 避免重复统计
            }
        }
        return ans;
    }
};

int main()
{
    return 0;
}