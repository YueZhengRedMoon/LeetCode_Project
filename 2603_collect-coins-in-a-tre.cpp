#include <iostream>
#include <vector>

class Solution
{
public:
    int collectTheCoins(std::vector<int> &coins, std::vector<std::vector<int>> &edges)
    {
        int n = coins.size();

        std::vector<std::vector<int>> graph(n);
        std::vector<int> deg(n, 0);
        for (const std::vector<int> &edge : edges)
        {
            int a = edge[0], b = edge[1];
            // 建图
            graph[a].push_back(b);
            graph[b].push_back(a);
            // 统计度数
            ++deg[a];
            ++deg[b];
        }

        // 对于没有金币的叶子节点，没有必要移动到它，通过拓扑排序将它们(以及连接它们父节点的边)删除
        // 因为不需要按照严格的拓扑顺序删除节点，所以可以不用队列来实现拓扑排序
        std::vector<int> q;
        int leftEdges = n - 1;  // 剩下的边数
        for (int x = 0; x < n; ++x)
        {
            if (deg[x] == 1 && coins[x] == 0)   // 没有金币的叶子节点，叶子节点的度数为1
            {
                --leftEdges;    // 删除与它的父节点之间的边，因为没有必要经过这条边
                q.push_back(x); // 将其加入拓扑”队列“中
            }
        }
        while (!q.empty())
        {
            int x = q.back();
            q.pop_back();
            for (int y : graph[x])
            {
                // y是x的父节点，在删除了x后，y也变成了叶子节点，且y不含金币
                if (--deg[y] == 1 && coins[y] == 0)
                {
                    q.push_back(y); // 没有必要走到y，准备删除y
                    --leftEdges;    // 删除y与其父节点之间的边，因为没有必要通过它
                    break;          // 因为x只可能有一个父节点，所以找到这样的节点就可跳出循环
                }
            }
        }

        // 再次拓扑排序，将所有含金币的叶子节点加入拓扑队列
        for (int x = 0; x < n; ++x)
        {
            if (deg[x] == 1 && coins[x] == 1)
                q.push_back(x); // 没有必要走到叶子节点上再收集金币，所以可以删除它们（以及与它们的父节点之间的边）
        }
        leftEdges -= q.size();  // 删除含有金币的叶子节点与其父节点之间的边
        while (!q.empty())
        {
            int x = q.back();
            q.pop_back();
            for (int y : graph[x])
            {
                // y是含金币叶子节点x的父节点，且删除x后y也变成了叶子节点
                if (--deg[y] == 1)
                {
                    // 由于可以拾取一个节点范围2以内的所有金币，所以只需要也必须走到y的父节点（设为z)就可以捡到x的金币
                    // 因此也没有必要走z与x之间的边，因此可以删除这条边
                    --leftEdges;
                    break;  // 因为x只可能有一个父节点，所以找到这样的节点就可跳出循环
                }
            }
        }

        // 剩下的边是必须要走的，且必定会往返2次
        // 如果所有点都可以被删除，当剩下两个点时，这两个点之间的边会被删除2次，导致剩余边数等于-1
        // 而答案应该是0，所以结果与0取最大值
        return std::max(leftEdges * 2, 0);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
