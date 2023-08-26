#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

const int MOD = 1000000007;

// 计算 (base ^ exp) % MOD 的结果
long long fast_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

// 求逆元
long long calc_inv(long long num) {
    return fast_pow(num, MOD - 2); // 使用费马小定理计算 num^(MOD-2) % MOD
}

// 求组合数
long long calc_combination(long long n, long long k) {
    if (k == 0 || k == n) {
        return 1;
    }
    long long result = 1;
    for (long long i = 1; i <= k; ++i) {
        result = (result * (n - i + 1)) % MOD;
        result = (result * calc_inv(i)) % MOD;
    }
    return result;
}


//int array[] = {10, 20, 30};
//std::cout << -2[array - 1];
int main()
{

    return 0;
}
