#include <iostream>
#include <vector>
#include <map>

/** 超时 */
class TreeAncestor2
{
public:
    TreeAncestor2(int n, std::vector<int> &parent) : firstParent(parent)
    {
        for (int i = 0; i < n; ++i)
        {
            std::pair<int, int> key = std::make_pair(i, 1);
            kthParent[key] = parent[i];
        }
    }

    int getKthAncestor(int node, int k)
    {
        std::pair<int, int> key = std::make_pair(node, k);
        auto it = kthParent.find(key);
        if (it == kthParent.end())
        {
            if (firstParent[node] != -1)
            {
                return kthParent[key] = getKthAncestor(firstParent[node], k - 1);
            }
            else
            {
                return -1;
            }
        }
        return it->second;
    }

private:
    std::map<std::pair<int, int>, int> kthParent;
    const std::vector<int> &firstParent;
};

class TreeAncestor
{
public:
    TreeAncestor(int n, std::vector<int> &parent)
    : ancestors(n, std::vector<int>(LOG, -1))
    {
        for (int i = 0; i < n; ++i)
        {
            ancestors[i][0] = parent[i];
        }
        for (int j = 1; j < LOG; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                if (ancestors[i][j - 1] != -1)
                {
                    // 2^(j-1) * 2 = 2^j
                    // 当前节点的第2^j个祖先，是它的第2^(j-1)个祖先第2^(j-1)个祖先
                    ancestors[i][j] = ancestors[ancestors[i][j - 1]][j - 1];
                }
            }
        }
    }

    int getKthAncestor(int node, int k)
    {
        for (int j = 0; j < LOG; ++j)
        {
            if ((k >> j) & 1)
            {
                node = ancestors[node][j];
                if (node == -1)
                {
                    return -1;
                }
            }
        }
        return node;
    }

private:
    constexpr static int LOG = 16;
    // ancestors[i][j]:表示i的第2^j个祖先
    std::vector<std::vector<int>> ancestors;
};


int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}