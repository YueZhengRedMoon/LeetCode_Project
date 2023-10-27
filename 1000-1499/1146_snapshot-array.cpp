#include <iostream>
#include <vector>
#include <unordered_set>

class SnapshotArray
{
public:
    SnapshotArray(int length) :
    cache(length, {std::make_pair(-1, 0)}),
    array(length, 0),
    snapId(0),
    size(length)
    {}

    void set(int index, int val)
    {
        if (array[index] != val)
        {
            array[index] = val;
            update.insert(index);
        }
    }

    int snap()
    {
        for (int i : update)
        {
            if (array[i] != cache[i].back().second)
            {
                cache[i].emplace_back(snapId, array[i]);
            }
        }
        std::unordered_set<int> empty;
        std::swap(update, empty);
        return snapId++;
    }

    int get(int index, int snap_id)
    {
        std::vector<std::pair<int, int>> &snaps = cache[index];
        // 找到第一个编号 <= snap_id的快照
        int left = 0, right = snaps.size(), retId = 0;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (snaps[mid].first <= snap_id)
            {
                retId = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return snaps[retId].second;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> cache;
    std::vector<int> array;
    int snapId;
    int size;
    std::unordered_set<int> update;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
