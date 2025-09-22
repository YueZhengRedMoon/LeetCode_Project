#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <tuple>
#include "../debug/debug.h"

struct PairHash
{
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);     // 计算第一个元素的哈希值
        auto h2 = std::hash<T2>{}(p.second);    // 计算第二个元素的哈希值

        // 组合哈希值（Boost风格）
        // 使用黄金比例相关的魔数
        h1 ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        return h1;
    }
};

class MovieRentingSystem
{
public:
    using Pair = std::pair<int, int>;

    MovieRentingSystem(int n, std::vector<std::vector<int>>& entries)
    {
        for (auto & entry : entries)
        {
            int shop = entry[0], movie = entry[1], price = entry[2];

            priceMap[{shop, movie}] = price;    // 记录该电影的价格
            addMovie(shop, movie, price);
        }
    }

    std::vector<int> search(int movie)
    {
        std::vector<int> res;
        const std::set<Pair>& movieSet = movieMap[movie];
        auto it = movieSet.begin();
        int cnt = 0;
        while (it != movieSet.end() && cnt < 5)
        {
            res.emplace_back(it->second);
            ++cnt;
            ++it;
        }
        return res;
    }

    void rent(int shop, int movie)
    {
        int price = priceMap.find({shop, movie})->second;
        auto it = iterMap.find({shop, movie})->second;
        movieMap[movie].erase(it);

        auto it2 = rentedMovie.insert({price, shop, movie}).first;
        rentedMovieIterMap[{shop, movie}] = it2;
    }

    void drop(int shop, int movie)
    {
        int price = priceMap.find({shop, movie})->second;   // 获取该电影的价格
        addMovie(shop, movie, price);

        // 将电影信息从已经借出的电影集合中删除
        auto it = rentedMovieIterMap.find({shop, movie})->second;
        rentedMovie.erase(it);
    }

    std::vector<std::vector<int>> report()
    {
        std::vector<std::vector<int>> res;
        auto it = rentedMovie.begin();
        int cnt = 0;
        while (it != rentedMovie.end() && cnt < 5)
        {
            auto [price, shop, movie] = *it;
            res.push_back({shop, movie});
            ++it;
            ++cnt;
        }
        return res;
    }

private:
    std::unordered_map<Pair, int, PairHash> priceMap;   // key: <shop, movie> value: price

    std::unordered_map<int, std::set<Pair>> movieMap; // key: movie, value: set<<price, shop>>
    std::unordered_map<Pair, std::set<Pair>::const_iterator, PairHash> iterMap; // key: <shop, movie>, value:set<<price, shop>>::iterator

    std::set<std::tuple<int, int, int>> rentedMovie;    // 已经借出的电影 <price, shop, movie>
    std::unordered_map<Pair, std::set<std::tuple<int, int, int>>::const_iterator, PairHash> rentedMovieIterMap; // key:: <shop, movie>

    // 将一部电影的信息加入到数据结构中存储（假定此电影的信息此前未存储）
    void addMovie(int shop, int movie, int price)
    {
        auto it = movieMap[movie].insert({price, shop}).first;
        iterMap[{shop, movie}] = it;
    }
};

int main()
{
    std::vector<std::vector<int>> entries = {{0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {1, 1, 4}, {1, 2, 7}, {2, 1, 5}};
    MovieRentingSystem sys(3, entries);

    std::vector<int> res1 = sys.search(1);
    debug::printVector(res1);

    sys.rent(0, 1);
    sys.rent(1, 2);

    std::vector<std::vector<int>> res2 = sys.report();
    debug::printVector2D(res2);

    sys.drop(1, 2);
    std::vector<int> res3 = sys.search(2);
    debug::printVector(res3);
    return 0;
}
