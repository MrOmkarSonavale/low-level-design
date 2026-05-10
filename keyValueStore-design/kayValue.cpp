#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <chrono>
#include <mutex>

using namespace std;

class LRUCache
{
private:
    struct Node
    {
        string key;
        string value;

        long long expiryTime;

        Node *prev;
        Node *next;

        Node(string k, string v, long long exp)
            : key(k),
              value(v),
              expiryTime(exp),
              prev(nullptr),
              next(nullptr) {}
    };

    int capacity;

    unordered_map<string, Node *> cache;

    Node *head;
    Node *tail;

    mutex mtx;

    struct Compare
    {
        bool operator()(pair<long long, string> &a,
                        pair<long long, string> &b)
        {
            return a.first > b.first;
        }
    };

    priority_queue<
        pair<long long, string>,
        vector<pair<long long, string>>,
        Compare>
        minHeap;

private:
    long long currentTimeMillis()
    {
        return chrono::duration_cast<
                   chrono::milliseconds>(
                   chrono::system_clock::now()
                       .time_since_epoch())
            .count();
    }

    // remove node from DLL
    void removeNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // add node right after head
    void addToFront(Node *node)
    {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    // move accessed node to front
    void moveToFront(Node *node)
    {
        removeNode(node);
        addToFront(node);
    }

    // remove least recently used
    void evictLRU()
    {

        Node *lru = tail->prev;

        if (lru == head)
            return;

        removeNode(lru);

        cache.erase(lru->key);

        delete lru;
    }

    // remove expired keys
    void cleanupExpiredKeys()
    {

        long long now = currentTimeMillis();

        while (!minHeap.empty())
        {

            auto top = minHeap.top();

            long long expiry = top.first;
            string key = top.second;

            if (expiry > now)
                break;

            minHeap.pop();

            if (cache.find(key) == cache.end())
                continue;

            Node *node = cache[key];

            // ignore stale heap entries
            if (node->expiryTime != expiry)
                continue;

            removeNode(node);

            cache.erase(key);

            delete node;
        }
    }

public:
    LRUCache(int cap)
    {

        capacity = cap;

        head = new Node("", "", 0);
        tail = new Node("", "", 0);

        head->next = tail;
        tail->prev = head;
    }

    // PUT
    void put(string key,
             string value,
             int ttlSeconds)
    {

        lock_guard<mutex> lock(mtx);

        cleanupExpiredKeys();

        long long expiry =
            currentTimeMillis() + ttlSeconds * 1000LL;

        // update existing key
        if (cache.find(key) != cache.end())
        {

            Node *node = cache[key];

            node->value = value;
            node->expiryTime = expiry;

            moveToFront(node);

            minHeap.push({expiry, key});

            return;
        }

        // capacity full
        if (cache.size() >= capacity)
        {
            evictLRU();
        }

        Node *node =
            new Node(key, value, expiry);

        addToFront(node);

        cache[key] = node;

        minHeap.push({expiry, key});
    }

    // GET
    string get(string key)
    {

        lock_guard<mutex> lock(mtx);

        cleanupExpiredKeys();

        if (cache.find(key) == cache.end())
        {
            return "NOT FOUND";
        }

        Node *node = cache[key];

        long long now =
            currentTimeMillis();

        // expired
        if (node->expiryTime < now)
        {

            removeNode(node);

            cache.erase(key);

            delete node;

            return "EXPIRED";
        }

        // LRU update
        moveToFront(node);

        return node->value;
    }

    // DELETE
    void deleteKey(string key)
    {

        lock_guard<mutex> lock(mtx);

        if (cache.find(key) == cache.end())
            return;

        Node *node = cache[key];

        removeNode(node);

        cache.erase(key);

        delete node;
    }

    void display()
    {

        lock_guard<mutex> lock(mtx);

        cleanupExpiredKeys();

        Node *curr = head->next;

        cout << "\nCache State:\n";

        while (curr != tail)
        {

            cout << curr->key
                 << " -> "
                 << curr->value
                 << endl;

            curr = curr->next;
        }

        cout << endl;
    }
};

int main()
{

    LRUCache cache(3);

    cache.put("A", "Apple", 20);
    cache.put("B", "Ball", 20);
    cache.put("C", "Cat", 20);

    cache.display();

    // Access A
    cout << cache.get("A") << endl;

    // Add new key
    cache.put("D", "Dog", 20);

    cache.display();

    return 0;
}