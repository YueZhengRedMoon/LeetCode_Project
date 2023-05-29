#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>

struct Node
{
    int key;
    int val;
    int freq;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;
    Node(int key_ = 0, int val_ = 0, int freq_ = 0,
         const std::shared_ptr<Node> &prev_ = nullptr, const std::shared_ptr<Node> &next_ = nullptr)
         : key(key_), val(val_), freq(freq_), prev(prev_), next(next_) {}
};

class LRUCache
{
public:
    LRUCache() : front(std::make_shared<Node>()), back(std::make_shared<Node>()), size(0)
    {
        front->next = back;
        back->prev = front;
    }

    void add(std::shared_ptr<Node> &p)
    {
        p->next = front->next;
        front->next->prev = p;
        p->prev = front;
        front->next = p;
        ++size;
    }

    void remove(std::shared_ptr<Node> &p)
    {
        p->next->prev = p->prev;
        p->prev->next = p->next;
        --size;
    }

    std::shared_ptr<Node> removeLRU()
    {
        std::shared_ptr<Node> lru = back->prev;
        remove(lru);
        return lru;
    }

    bool empty() const
    {
        return size == 0;
    }
private:
    std::shared_ptr<Node> front;
    std::shared_ptr<Node> back;
    int size;
};

class LFUCache
{
public:
    LFUCache(int capacity) : maxSize(capacity), size(0), minFreq(0)
    {

    }

    int get(int key)
    {
        auto keyIt = keyMap.find(key);
        if (keyIt != keyMap.end())
        {
            increaseFreq(keyIt->second);
            return keyIt->second->val;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        auto keyIt = keyMap.find(key);
        if (keyIt != keyMap.end())
        {
            increaseFreq(keyIt->second);
            keyIt->second->val = value;
        }
        else
        {
            if (size >= maxSize)
            {
                auto minIt = sameFreq.find(minFreq);
                std::shared_ptr<Node> lfu = minIt->second.removeLRU();
                keyMap.erase(lfu->key);
                if (minIt->second.empty() && lfu->freq != 1)
                {
                    sameFreq.erase(minIt);
                }
                --size;
            }
            std::shared_ptr<Node> newNode = std::make_shared<Node>(key, value, 1);
            sameFreq[1].add(newNode);
            keyMap[key] = newNode;
            minFreq = 1;
            ++size;
        }
    }

private:
    int maxSize;                            // 缓存的最大容量
    int size;                               // 当前的容量
    int minFreq;
    std::unordered_map<int, std::shared_ptr<Node>> keyMap;
    std::unordered_map<int, LRUCache> sameFreq;       // 相同频率下的关键字

    void increaseFreq(std::shared_ptr<Node> &p)
    {
        int oldFreq = p->freq;
        auto it = sameFreq.find(oldFreq);
        it->second.remove(p);
        if (it->second.empty())
        {
            sameFreq.erase(oldFreq);
            if (oldFreq == minFreq)
            {
                ++minFreq;
            }
        }
        sameFreq[++p->freq].add(p);
    }
};

int main()
{
    int val;
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    val = lfu.get(1);
    std::cout << val << std::endl;
    lfu.put(3, 3);
    val = lfu.get(2);
    std::cout << val << std::endl;
    val = lfu.get(3);
    std::cout << val << std::endl;
    lfu.put(4, 4);
    val = lfu.get(1);
    std::cout << val << std::endl;
    val = lfu.get(3);
    std::cout << val << std::endl;
    val = lfu.get(4);
    std::cout << val << std::endl;
    return 0;
}
