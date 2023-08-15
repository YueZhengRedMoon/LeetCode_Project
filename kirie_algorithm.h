//
// Created by Kirie on 2023/5/4.
//

#ifndef __LEET_CODE_PROJECT_ALGORITHM_H
#define __LEET_CODE_PROJECT_ALGORITHM_H
#define likely(x) __builtin_expect(!!(x), 1)    // 表达式x很可能为真
#define unlikely(x) __builtin_expect(!!(x), 0)  // 表达式x很可能为假
#include <functional>
#include <iostream>
#include <forward_list>
#include <queue>
#include <limits>

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

    enum class GraphMode
    {
        DEFAULT,
        ADJ_MATRIX,
        ADJ_LIST
    };

    struct OutEdge
    {
        int to;
        int cost;
    };

    /** 求解有向图最短路的算法 */
    class ShortestPath
    {
    public:
        struct Edge
        {
            int from;
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
        const int inf{std::numeric_limits<int>::max()};

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

    class MinimumSpanningTree
    {
    public:
        MinimumSpanningTree(int edgeNum_, int vertexNum_, std::vector<std::vector<int>> &edges_):
        edgeNum(edgeNum_),
        vertexNum(vertexNum_),
        adjMatrix(vertexNum_, std::vector<int>(vertexNum_, inf)),
        adjList(vertexNum_),
        visited(vertexNum_),
        minCost(vertexNum_)
        {
            for (const auto &e : edges_)
            {
                adjMatrix[e[0]][e[1]] = e[2];
                adjMatrix[e[1]][e[0]] = e[2];

                adjList[e[0]].push_front({e[1], e[2]});
                adjList[e[1]].push_front({e[0], e[2]});
            }
        }

        int prim(GraphMode mode)
        {
            if (mode == GraphMode::ADJ_MATRIX)
                return adjMatrixPrim();
            else
                return adjListPrim();
        }

    private:
        int edgeNum;
        int vertexNum;
        std::vector<std::vector<int>> adjMatrix;
        std::vector<std::forward_list<OutEdge>> adjList;
        std::vector<bool> visited;  // visited[i]:顶点i是否已经加入生成树
        std::vector<int> minCost;   // 从生成树集合X出发，到每个顶点的最小权值
        const int inf{std::numeric_limits<int>::max()};

        int adjMatrixPrim()
        {
            for (int i = 0; i < vertexNum; ++i)
            {
                minCost[i] = inf;
                visited[i] = false;
            }
            minCost[0] = 0;
            int res = 0;
            while (true)
            {
                int v = -1;
                // 从不属于X的顶点中选取出X到其权值最小的顶点
                for (int u = 0; u < vertexNum; ++u)
                {
                    if (!visited[u] && (v == -1 || minCost[u] < minCost[v]))
                    {
                        v = u;
                    }
                }
                // 所有顶点都已经加入生成树
                if (v == -1)
                    break;
                // 将顶点v加入X
                visited[v] = true;
                // 把边的长度加入到结果里
                res += minCost[v];
                // 新的顶点加入到了生成树中，更新剩余顶点到生成树的最小权值
                for (int u = 0; u < vertexNum; ++u)
                {
                    minCost[u] = std::min(minCost[u], adjMatrix[v][u]);
                }
            }
            return res;
        }

        int adjListPrim()
        {
            for (int i = 0; i < vertexNum; ++i)
            {
                minCost[i] = inf;
                visited[i] = false;
            }
            minCost[0] = 0;
            // first是顶点到生成树的成本，second是顶点的编号
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
            queue.emplace(0, 0);
            int res = 0, vertexInTree = 0;
            while (vertexInTree < vertexNum && !queue.empty())
            {
                auto [cost, v] = queue.top();
                queue.pop();
                if (visited[v] || cost > minCost[v])
                    continue;
                visited[v] = true;
                res += minCost[v];
                ++vertexInTree;
                for (const auto &e : adjList[v])
                {
                    if (!visited[e.to] && e.cost < minCost[e.to])
                    {
                        minCost[e.to] = e.cost;
                        queue.emplace(minCost[e.to], e.to);
                    }
                }
            }
            return res;
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

    class HeapBase
    {
    public:
        HeapBase(int maxSize) : size(0), capacity(maxSize), heap(capacity) {}

        bool isEmpty() const
        {
            return size <= 0;
        }

        virtual void push(int x) = 0;
        virtual int pop() = 0;

    protected:
        int size;
        int capacity;
        std::vector<int> heap;
    };

    class MinHeap : public HeapBase
    {
    public:
        MinHeap(int maxSize) : HeapBase(maxSize) {}

        virtual void push(int x) override
        {
            // 自己节点的编号
            int i = size++;
            while (i > 0)
            {
                // 父节点的编号
                int p = (i - 1) / 2;

                // 如果已经符合小顶堆的要求，则退出
                if (heap[p] <= x)
                    break;

                // 不满足小顶堆的要求，把父节点的值放下来，而把自己提上去
                heap[i] = heap[p];
                i = p;
            }
            heap[i] = x;
        }

        virtual int pop() override
        {
            // 堆顶最小值
            int ret = heap[0];

            // 要提到根的数值
            int x = heap[--size];

            // 从根开始向下交换
            int i = 0;
            while (i * 2 + 1 < size)
            {
                int left = i * 2 + 1, right = i * 2 + 2;
                int min = left; // 左右孩子中的最小值
                if (right < size && heap[right] < heap[left])
                    min = right;

                // 已经满足小顶堆的性质，退出
                if (heap[min] >= x)
                    break;

                // 把子节点的值提上来
                heap[i] = heap[min];
                i = min;
            }

            heap[i] = x;
            return ret;
        }
    };

    class MaxHeap : public HeapBase
    {
    public:
        MaxHeap(int maxSize) : HeapBase(maxSize) {}

        virtual void push(int x) override
        {
            // 自己节点的编号
            int i = size++;

            while (i > 0)
            {
                // 父节点的编号
                int p = (i - 1) / 2;

                // 已经满足大顶堆的性质，退出
                if (heap[p] >= x)
                    break;

                // 把父节点的数值放下来，而把自己提上去
                heap[i] = heap[p];
                i = p;
            }

            heap[i] = x;
        }

        virtual int pop() override
        {
            // 堆顶最大值
            int ret = heap[0];

            // 要提到根的数值
            int x = heap[--size];

            // 从根开始向下交换
            int i = 0;
            while (i * 2 + 1 < size)
            {
                int left = i * 2 + 1, right = i * 2 + 2;
                int max = left; // 左右孩子中的最大值
                if (right < size && heap[left] < heap[right])
                    max = right;

                // 已经满足大顶堆的性质，退出
                if (heap[max] <= x)
                    break;

                // 把子节点的值提上来
                heap[i] = heap[max];
                i = max;
            }
            heap[i] = x;

            return ret;
        }
    };

    /** 快速排序算法 */
    template<typename T>
    int partition(std::vector<T> &arr, int low, int high)
    {
        int pivot = arr[(low + high) / 2];
        int i = low - 1, j = high + 1;
        while (true)
        {
            do
            {
                ++i;
            } while (arr[i] < pivot);
            do
            {
                --j;
            } while (arr[j] > pivot);

            if (i >= j)
                return j;

            std::swap(arr[i], arr[j]);
        }
    }

    template<typename T>
    void quickSort(std::vector<int> &arr, int low, int high)
    {
        if (low < high)
        {
            int pivotIndex = partition(arr, low, high);
            quickSort<T>(arr, low, pivotIndex);
            quickSort<T>(arr, pivotIndex + 1, high);
        }
    }

}   // namespace kirie

#endif //__LEET_CODE_PROJECT_ALGORITHM_H
