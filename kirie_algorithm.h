//
// Created by Kirie on 2023/5/4.
//

#ifndef __LEET_CODE_PROJECT_ALGORITHM_H
#define __LEET_CODE_PROJECT_ALGORITHM_H
#include <functional>
#include <iostream>
#include <forward_list>
#include <queue>

namespace kirie
{
    /** 在区间[0, n)根据可调用对象comp找到第一个大于或大于等于target的数的索引，传入comp的参数是区间的中点mid，
     *  comp应该具有如下形式：
     *  return nums[mid] > target;  // 在nums[0:n)中找到第一个(最小的)大于target的数，返回其索引
     *  return nums[mid] >= target; // 在nums[0:n)中找到第一个(最小的)大于等于target的数，返回其索引
     *  */
    int minGreaterEqual(int n, std::function<bool(int)> comp)
    {
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            // nums[mid] >= target
            // nums[mid] > target
            if (comp(mid))
            {
                right = mid;
            }
            // nums[mid] < target
            // nums[mid] <= target
            else
            {
                // nums[mid] < target --> nums[mid + 1]可能>=target
                // nums[mid] <= target --> nums[mid + 1]可能>target
                left = mid + 1;
            }
        }
        return left;
    }

    /** 在区间[0, n)根据可调用对象comp找到最后一个小于或小于等于target的数的索引，传入comp的参数是区间的中点mid，
     *  comp应该具有如下形式：
     *  return nums[mid] < target;  // 在nums[0:n)中找到第一个(最大的)小于target的数，返回其索引
     *  return nums[mid] <= target; // 在nums[0:n)中找到第一个(最大的)小于等于target的数，返回其索引
     *  */
    int maxLessEqual(int n, std::function<bool(int)> comp)
    {
        int left = 0, right = n;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            // nums[mid] <= target
            // nums[mid] < target
            if (comp(mid))
            {
                left = mid + 1;
            }
            // nums[mid] > target
            // nums[mid] >= target
            else
            {
                right = mid;
            }
        }
        return left - 1;
    }

    template <typename T>
    T max(const T& t)
    {
        return t;
    }

    template <typename T, typename... Args>
    T max(const T& t, const Args&... args)
    {
        return std::max(t, max(args...));
    }

    template <typename T>
    T min(const T& t)
    {
        return t;
    }

    template <typename T, typename... Args>
    T min(const T& t, const Args&... args)
    {
        return std::min(t, min(args...));
    }

    /** 求解有向图最短路的算法 */
    class ShortestPath
    {
    public:
        enum class GraphMode
        {
            DEFAULT,
            ADJ_MATRIX,
            ADJ_LIST
        };

        struct Edge
        {
            int from;
            int to;
            int cost;
        };

        struct OutEdge
        {
            int to;
            int cost;
        };

        ShortestPath(int edgeNum_, int vertexNum_, std::vector<std::vector<int>> &edges_)
        : edgeNum(edgeNum_),
          vertexNum(vertexNum_),
          distance(vertexNum_),
          edges(edgeNum_),
          visited(vertexNum_),
          adjMatrix(vertexNum_, std::vector<int>(vertexNum_, inf)),
          adjList(vertexNum_)
        {
            for (int i = 0; i < edgeNum; ++i)
            {
                edges[i].from = edges_[i][0];
                edges[i].to = edges_[i][1];
                edges[i].cost = edges_[i][2];

                adjMatrix[edges_[i][0]][edges_[i][1]] = edges_[i][2];

                adjList[edges_[i][0]].push_front({edges_[i][1], edges_[i][2]});
            }
        }

        /** Bellman-Ford算法，可以计算图中存在负边的情况，但是不能处理存在负圈的情况，
         *  时间复杂度：O(VE)，其中V为顶点数，E为边数。
         *  如果不存在负圈，则bellman-Ford算法最多循环V-1次，返回循环的次数 */
        int bellmanFord(int source)
        {
            std::fill(distance.begin(), distance.end(), inf);
            distance[source] = 0;
            bool update = true;
            int iteration = 0;
            while (update && iteration < vertexNum - 1)
            {
                update = false;
                for (int i = 0; i < edgeNum; ++i)
                {
                    Edge &e = edges[i];
                    if (distance[e.from] != inf && distance[e.to] > distance[e.from] + e.cost)
                    {
                        distance[e.to] = distance[e.from] + e.cost;
                        update = true;
                    }
                }
                ++iteration;
            }
            return iteration;
        }

        /** 判断图中是否存在负圈 */
        bool hasNegativeLoop()
        {
            std::fill(distance.begin(), distance.end(), 0);
            for (int i = 0; i < vertexNum; ++i)
            {
                for (int j = 0; j < edgeNum; ++j)
                {
                    Edge &e = edges[j];
                    if (distance[e.to] > distance[e.from] + e.cost)
                    {
                        distance[e.to] = distance[e.from] + e.cost;
                        // 如果第V次仍然更新了，则存在负圈
                        if (i == vertexNum - 1)
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        /** 使用Dijkstra算法求解最短路， */
        void dijkstra(int source, GraphMode graphMode)
        {
            switch (graphMode)
            {
                case GraphMode::ADJ_MATRIX:
                    adjMatrixDijkstra(source);
                    break;
                case GraphMode::ADJ_LIST:
                    adjListDijkstra(source);
                    break;
                default:
                    break;
            }
        }

        /** 在计算完最短路后获取从源点到所有顶点的最短路 */
        std::vector<int> getDistance()
        {
            return distance;
        }

    private:
        int edgeNum;
        int vertexNum;
        std::vector<int> distance;
        std::vector<Edge> edges;
        std::vector<bool> visited;  // visited[i]:源点到顶点i的最短路是否已经求出
        std::vector<std::vector<int>> adjMatrix;
        std::vector<std::forward_list<OutEdge>> adjList;
        const int inf{0x3f3f3f3f};

        /** 使用邻接矩阵版本的Dijkstra算法求解最短路 */
        void adjMatrixDijkstra(int source)
        {
            std::fill(distance.begin(), distance.end(), inf);
            std::fill(visited.begin(), visited.end(), false);
            distance[source] = 0;
            while (true)
            {
                int v = -1;
                // 从未找出最短路的顶点中选择一个距离源点距离最短的顶点
                for (int u = 0; u < vertexNum; ++u)
                {
                    if (!visited[u] && (v == -1 || distance[u] < distance[v]))
                    {
                        v = u;
                    }
                }

                if (v == -1)
                {
                    break;
                }
                visited[v] = true;  // 从源点到v的最短路已经找到

                // 根据已经找到最短路的顶点v，更新其出边的目标顶点的最短路
                for (int u = 0; u < vertexNum; ++u)
                {
                    distance[u] = std::min(distance[u], distance[v] + adjMatrix[v][u]);
                }
            }
        }

        /** 使用邻接表版本的Dijkstra算法求解最短路 */
        void adjListDijkstra(int source)
        {
            std::priority_queue<std::pair<int, int>> queue; // first:最短距离，second:点的编号
            std::fill(distance.begin(), distance.end(), inf);
            distance[source] = 0;
            queue.emplace(0, source);
            while (!queue.empty())
            {
                auto [minDis, v] = queue.top(); // minDis:在上一轮迭代中找到的从源点到v的最短距离（不一定是最短的）
                queue.pop();
                if (distance[v] < minDis) continue;
                // 根据已经找到最短路的顶点v，更新其出边的目标顶点的最短路
                for (const OutEdge &e : adjList[v])
                {
                    if (distance[e.to] > distance[v] + e.cost)
                    {
                        distance[e.to] = distance[v] + e.cost;
                        queue.emplace(distance[e.to], e.to);
                    }
                }
            }
        }
    };

    /** 快速选择算法，将第n小的元素放在第n个位置，
     *  所有比它小的元素都在它的左边，所有比它大的元素都在它的右面 */
    template<typename RandomIt>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last)
    {
        if (first >= last || nth >= last)
            return;

        // 选择一个枢轴，使得所有比他小的元素都在它的左边，所有比它大的元素都在它的右边
        RandomIt pivot = std::prev(last);
        RandomIt left = first;
        RandomIt right =std::prev(last);

        while (left < right)
        {
            // 找到第一个大于等于枢轴的元素，准备将它交换到枢轴的右边
            while (left < right && *left < *pivot)
                ++left;
            // 找到第一个小于枢轴的元素，准备将它交换到枢轴的左边
            while (left < right && *right >= *pivot)
                --right;
            // 交换两个元素到正确的位置
            if (left < right)
                std::iter_swap(left, right);
        }

        // 循环结束时left指向的是最小的 >= pivot的元素，将其与枢轴交换
        std::iter_swap(left, pivot);

        // 枢轴元素正好是第n个元素，找到了第n小的元素
        if (left == nth)
            return;
        // 枢轴元素在第n个元素左边，在枢轴元素的右边继续寻找
        else if (left < nth)
            kirie::nth_element(left + 1, nth, last);
        // 枢轴元素在第n个元素的右边，在枢轴元素的左边继续寻找
        else
            kirie::nth_element(first, nth, left);
    }
}   // namespace kirie

#endif //__LEET_CODE_PROJECT_ALGORITHM_H
