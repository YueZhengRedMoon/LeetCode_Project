#include <iostream>
#include <vector>
#include <queue>

int main()
{
    int N, M, K, Sr, Sc, Er, Ec;
    std::cin >> N >> M >> K >> Sr >> Sc >> Er >> Ec;
    std::vector<std::vector<char>> g(N + 2, std::vector<char>(M + 2, '.'));
    for (int i = 0; i < K; ++i)
    {
        int R, C;
        char Type;
        std::cin >> R >> C >> Type;
        g[R][C] = Type;
    }
    // 围墙
    for (int j = 0; j < M + 2; ++j)
    {
        g[0][j] = '#';
        g[M + 1][j] = '#';
    }
    for (int i = 0; i < N + 2; ++i)
    {
        g[i][0] = '#';
        g[i][N + 1] = '#';
    }

    const int INF = INT_MAX;
    // roll[i][j][k]:从k方向到达g[i][j]的最小滚动次数，k=0,1,2,3分别表示上,下,左,右
    std::vector<std::vector<std::vector<int>>> roll(N + 2, std::vector<std::vector<int>>(M + 2, std::vector<int>(4, INF)));
    roll[Sr][Sc][0] = roll[Sr][Sc][1] = roll[Sr][Sc][2] = roll[Sr][Sc][3] = 0;

    std::queue<std::vector<int>> q;
    q.push({Sr, Sc, 0});
    while (!q.empty())
    {
        std::vector<int>& front = q.front();
        int x = front[0], y = front[1], r = front[2];
        q.pop();
    }
    return 0;
}
