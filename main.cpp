#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<std::vector<int>> edges{{0, 2, 1}, {1, 2, 2}, {2, 3, 3}, {1, 4, 10}, {2, 5, 7}, {3, 5, 1},
                                        {3, 6, 5}, {4, 5, 5}, {5, 6, 8}};
    int edgeNum = 9;
    int vertexNum = 7;
    kirie::MinimumSpanningTree mst(edgeNum, vertexNum, edges);
    int res = mst.prim(kirie::GraphMode::ADJ_LIST);
    std::cout << res << std::endl;
    return 0;
}
