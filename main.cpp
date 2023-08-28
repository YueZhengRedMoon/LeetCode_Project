#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::string s = "abbcccdddd";

    int cnt[26]{0};
    int a = 1, b = 1;
    for (int i = 0; i < s.size(); ++i)
    {
        a *= (i + 1);
        b *= ++cnt[s[i] - 'a'];
    }
    logObj(a / b);

    std::string cur(s);
    std::unordered_set<std::string> set;
    do
    {
        // logObj(cur);
        set.insert(cur);
    } while (std::next_permutation(cur.begin(), cur.end()));
    logObj(set.size());
    return 0;
}
