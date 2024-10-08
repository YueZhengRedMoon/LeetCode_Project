#include <iostream>
#include <vector>
#include <numeric>
#include <execution>
#include <chrono>

int main()
{
    const int MAX_N = 1'000'000'000;
    std::vector<int> a(MAX_N);

    auto start = std::chrono::steady_clock::now();
    std::iota(a.begin(), a.end(), 0);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "O(n=1e9)初始化用时：" << duration.count() << "毫秒" <<std::endl;

    start = std::chrono::steady_clock::now();
    long long sum = std::reduce(std::execution::par, a.begin(), a.end(), 0ll, std::plus<>());
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "reduce求和用时：" << duration.count() << "毫秒，sum = " << sum << std::endl;

    start = std::chrono::steady_clock::now();
    sum = std::accumulate(a.begin(), a.end(), 0ll);
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "accumulate求和用时：" << duration.count() << "毫秒，sum = " << sum << std::endl;
    return 0;
}
