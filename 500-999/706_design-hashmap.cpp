#include <iostream>
#include <vector>

class MyHashMap
{
public:
    MyHashMap() : hashMap(1'000'001, -1) {}

    void put(int key, int value)
    {
        hashMap[key] = value;
    }

    int get(int key)
    {
        return hashMap[key];
    }

    void remove(int key)
    {
        hashMap[key] = -1;
    }

private:
    std::vector<int> hashMap;
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
