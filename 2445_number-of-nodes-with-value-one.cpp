#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int numberOfNodes(int n, std::vector<int> &queries)
    {
        int ans = 0;
        std::vector<int> tree(n + 1, 0);
        for (int q : queries)
        {
            tree[q] = !tree[q];
        }
        std::function<void(int)> dfs = [&](int node) {
            if (node > n)
                return;
            int parent = node / 2;
            tree[node] = tree[node] == 1 ? !tree[parent] : tree[parent];
            ans += tree[node];
            dfs(2 * node);
            dfs(2 * node + 1);
        };
        dfs(1);
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
