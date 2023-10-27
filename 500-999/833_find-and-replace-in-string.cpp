#include <iostream>
#include <vector>
#include <functional>
#include <sstream>

class Solution
{
public:
    std::string findReplaceString(std::string s, std::vector<int> &indices, std::vector<std::string> &sources,
                                  std::vector<std::string> &targets)
    {
        int k = indices.size();

        // 将操作数组按照indices从小到大排序
        if (k > 1)
        {
            std::function<int(int, int)> partition = [&](int low, int high) -> int
            {
                int pivot = indices[(low + high) / 2], i = low - 1, j = high + 1;
                while (true)
                {
                    do
                    {
                        ++i;
                    } while (indices[i] < pivot);
                    do
                    {
                        --j;
                    } while (indices[j] > pivot);

                    if (i >= j)
                        return j;

                    std::swap(indices[i], indices[j]);
                    std::swap(sources[i], sources[j]);
                    std::swap(targets[i], targets[j]);
                }
            };

            std::function<void(int, int)> quickSort = [&](int low, int high) -> void
            {
                if (low >= high)
                    return;

                int pivotIndex = partition(low, high);
                quickSort(low, pivotIndex);
                quickSort(pivotIndex + 1, high);
            };

            quickSort(0, k - 1);
        }

        std::ostringstream oss;
        int i = 0, j = 0, n = s.size();
        while (i < n)
        {
            if (j < k && i == indices[j])
            {
                bool match = true;
                int sourceLen = sources[j].size();
                for (int p = 0; p < sourceLen; ++p)
                {
                    if (i + p >= n || s[i + p] != sources[j][p])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                {
                    oss << targets[j];
                    i += sourceLen;
                }
                else
                {
                    oss << s[i++];
                }
                ++j;
            }
            else
            {
                oss << s[i++];
            }
        }

        return oss.str();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
