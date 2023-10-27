#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    int nthSuperUglyNumber(int n, std::vector<int> &primes)
    {
        std::sort(primes.begin(), primes.end());

        std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
        heap.push(1);
        std::unordered_set<int> seen;

        int superUgly;
        int intMax = std::numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
        {
            superUgly = heap.top();
            heap.pop();
            // ugly * prime <= intMax -> prime <= intMax / superUgly
            int maxPrime = intMax / superUgly;
            for (int j = 0; j < primes.size() && primes[j] <= maxPrime; ++j)
            {
                int nextSuperUgly = superUgly * primes[j];
                if (seen.find(nextSuperUgly) == seen.end())
                {
                    heap.push(nextSuperUgly);
                    seen.insert(nextSuperUgly);
                }
            }
        }

        return superUgly;
    }
};

class Solution2
{
public:
    int nthSuperUglyNumber(int n, std::vector<int> &primes)
    {
        int primesSize = primes.size();
        // dp[i]表示第i个丑数
        std::vector<int> dp(n + 1);
        dp[1] = 1;
        std::vector<int> p(primesSize, 1);

        int intMax = std::numeric_limits<int>::max();
        for (int i = 2; i <= n; ++i)
        {
            int minNext = intMax;
            for (int j = 0; j < primesSize; ++j)
            {
                // dp[p[j]] * primes[j] <= intMax
                // dp[p[j]] <= intMax / primes[j]
                if (dp[p[j]] <= intMax / primes[j])
                {
                    minNext = std::min(minNext, dp[p[j]] * primes[j]);
                }
            }
            dp[i] = minNext;
            for (int j = 0; j < primesSize; ++j)
            {
                if ((dp[p[j]] <= intMax / primes[j]) && (dp[p[j]] * primes[j] == dp[i]))
                {
                    ++p[j];
                }
            }
        }

        return dp[n];
    }
};

int main()
{
    Solution2 solution;
    int n = 100000;
    std::vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,
                               113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,
                               239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,
                               373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
                               503,509,521,523,541};
    int superUgly = solution.nthSuperUglyNumber(n, primes);
    // 284445
    std::cout << superUgly << std::endl;
    return 0;
}
