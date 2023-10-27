#include <iostream>
#include <vector>

class ZigzagIterator
{
public:
    ZigzagIterator(std::vector<int> &v1, std::vector<int> &v2)
    {
        vectors.push_back(v1);
        vectors.push_back(v2);
        iterNext.push_back(1);
        iterNext.push_back(0);
        iterIndex.resize(2, 0);
        iter = 0;
        if (v1.empty())
        {
            iterNext[1] = 1;
            iter = 1;
        }
    }

    int next()
    {
        int res = vectors[iter][iterIndex[iter]];
        ++iterIndex[iter];
        iter = getNextIter(iter);
        return res;
    }

    bool hasNext()
    {
        return iterIndex[iter] < vectors[iter].size();
    }

private:
    std::vector<std::vector<int>> vectors;
    std::vector<int> iterNext;
    std::vector<int> iterIndex;
    int iter;

    int getNextIter(int i)
    {
        int j;
        for (j = iterNext[i]; i != j && iterIndex[j] == vectors[j].size(); j = iterNext[j]);
        return iterNext[i] = j;
    }
};


int main()
{
    std::vector<int> v1 = {1, 2}, v2 = {3, 4, 5, 6};
    ZigzagIterator zigzagIterator(v1, v2);
    while (zigzagIterator.hasNext())
    {
        std::cout << zigzagIterator.next() << std::endl;
    }
    return 0;
}