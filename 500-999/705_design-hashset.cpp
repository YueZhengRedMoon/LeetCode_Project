#include <iostream>
#include <vector>
#include <memory>
#include <bitset>


class MyHashSet
{
public:
    MyHashSet() = default;

    void add(int key)
    {
        set.set(key);
    }

    void remove(int key)
    {
        set.reset(key);
    }

    bool contains(int key)
    {
        return set.test(key);
    }

private:
    std::bitset<1'000'001> set;
};

namespace Solution1
{
    struct Node
    {
        int key;
        std::shared_ptr<Node> next;

        Node(int k) : key(k), next(nullptr) {}
    };

    class MyHashSet
    {
    public:
        MyHashSet() : nodes(10009) {}

        void add(int key)
        {
            std::size_t idx = getIndex(key);
            std::shared_ptr<Node> p = nodes[idx], prev = nullptr;
            while (p)
            {
                if (p->key == key)
                    return;
                prev = p;
                p = p->next;
            }
            if (prev)
                prev->next = std::make_shared<Node>(key);
            else
                nodes[idx] = std::make_shared<Node>(key);
        }

        void remove(int key)
        {
            std::size_t idx = getIndex(key);
            std::shared_ptr<Node> p = nodes[idx], prev = nullptr;
            while (p)
            {
                if (p->key == key)
                {
                    if (prev)
                        prev->next = p->next;
                    else
                        nodes[idx] = nullptr;
                    break;
                }
                prev = p;
                p = p->next;
            }
        }

        bool contains(int key)
        {
            std::size_t idx = getIndex(key);
            std::shared_ptr<Node> p = nodes[idx];
            while (p)
            {
                if (p->key == key)
                    return true;
                p = p->next;
            }
            return false;
        }

    private:
        std::vector<std::shared_ptr<Node>> nodes;
        std::hash<int> hashFun;

        std::size_t getIndex(int key)
        {
            // 因为 nodes 的长度只有 10009，对应的二进制的 10011100011001（总长度为 64 位，其余高位都是 0）
            // 为了让 key 对应的 hash 高位也参与运算，这里对 hashCode 进行右移异或
            // 使得 hashCode 的高位随机性和低位随机性都能体现在低 16 位中
            std::size_t hash = hashFun(key);
            hash ^= (hash >> 16);
            hash ^= (hash >> 16);
            hash ^= (hash >> 16);
            return hash % nodes.size();
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
