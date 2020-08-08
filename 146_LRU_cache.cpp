#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;

class LRUCache {
public:
    explicit LRUCache(int capacity) : data(capacity), capacity(capacity) {}

    int get(int key) {
        auto it = data.find(key);
        if (it != data.end()) {
            history[key] = stamp++;
            return it->second;
        }
        else
            return -1;
    }

    void put(int key, int value) {
        // 将最久未使用的数据删除
        if (data.size() >= capacity && data.find(key) == data.end()) {
            auto it = history.begin();
            auto oldest = it;
            while (it != history.end()) {
                if (oldest->second > it->second)
                    oldest = it;
                ++it;
            }
            data.erase(oldest->first);
            history.erase(oldest);
        }
        data[key] = value;
        history[key] = stamp++;
    }

private:
    std::unordered_map<int, int> data;
    std::unordered_map<int, int> history;
    int capacity;
    int stamp = 0;
};

/*
 * 使用双向链表保存数据，使用哈希表保存key到链表节点的映射以实现快速查找，双向链表中中越靠前越新。
 * 1、为什么需要双向链表？查找到一个值时需要将其摘下放到头节点后，所以必须要从节点本身得到前驱。
 * 2、为什么链表节点需要key和value两个数据域？因为删除最久未使用的节点时是通过链表查找，但需要
 *    根据它的key来删除哈希表中的相应记录。
 */
struct DNode {
    int key = 0;
    int value = 0;
    DNode *prev = nullptr;
    DNode *next = nullptr;
};

class LRUCache1 {  // 提交时改名
public:
    // 提交时改名
    explicit LRUCache1(int capacity) : capacity{capacity}, map(capacity) {
        list = new DNode;
        list->next = list->prev = list;
    }

    ~LRUCache1() {  // 提交时改名
        DNode *p = list->next;
        while (p != list) {
            DNode *t = p->next;
            delete p;
            p = t;
        }
        delete list;
    }

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end())
            return -1;
        moveToHead(it->second);
        return it->second->value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            map[key]->value = value;
            moveToHead(map[key]);
        } else {
            if (size == capacity) {
                map.erase(list->prev->key);
                deleteTail();
                --size;
            }
            auto *node = new DNode;
            node->key = key;
            node->value = value;
            insertToHead(node);
            map[key] = node;
            ++size;
        }
    }

private:
    int capacity = 0;
    int size = 0;
    DNode *list = nullptr;   // 双向循环链表
    std::unordered_map<int, DNode *> map;

    // 将node移动到list首部
    void moveToHead(DNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        insertToHead(node);
    }

    // 在list首部插入一个节点
    void insertToHead(DNode *node) {
        node->prev = list;
        node->next = list->next;
        list->next->prev = node;
        list->next = node;
    }

    // 删除尾部节点
    void deleteTail() {
        if (list->prev == list) // 只有头节点
            return ;
        DNode *tail = list->prev;
        tail->prev->next = list;
        list->prev = tail->prev;
        delete tail;
    }
};

int main() {
    LRUCache1 cache1(2);

    cache1.put(1, 1);
    cache1.put(2, 2);

    // 1
    cout << cache1.get(1) << ", ";

    // 该操作会使得密钥2作废
    cache1.put(3, 3);

    // -1 (未找到)
    cout << cache1.get(2) << ", ";

    // 该操作会使得密钥1作废
    cache1.put(4, 4);

    // -1 (未找到)
    cout << cache1.get(1) << ", ";

    // 3
    cout << cache1.get(3) << ", ";

    // 4
    cout << cache1.get(4) << ", ";
    cout << endl;


    LRUCache1 cache2(2);

    cache2.put(2, 1);
    cache2.put(1, 1);
    cache2.put(2, 3);
    cache2.put(4, 1);

    // -1
    cout << cache2.get(1) << ", ";

    // 3
    cout << cache2.get(2) << ", ";
    cout << endl;

    return 0;
}
