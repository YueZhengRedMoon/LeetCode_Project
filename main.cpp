#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<std::vector<int>> edges = {{0, 1, 2}, {2, 0, 5}, {1, 2, 4}, {2, 3, 2}, {1, 3, 6},
                                           {1, 4, 10}, {3, 5, 1}, {5, 4, 3}, {4, 6, 5}, {5, 6, 9}};
    int vertexNum = 7;
    int edgeNum = edges.size();
    kirie::ShortestPath shortestPath(edgeNum, vertexNum, edges);

    shortestPath.dijkstra(0, kirie::ShortestPath::GraphMode::ADJ_LIST);
    std::vector<int> cost = shortestPath.getDistance();
    debug::printVector(cost);

    shortestPath.bellmanFord(0);
    cost = shortestPath.getDistance();
    debug::printVector(cost);
    return 0;
}
