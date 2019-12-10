#ifndef LRUSTACK_H
#define LRUSTACK_H
// lru memory
struct LRU {
    int pid, allocId;
    LRU *next, *prev;
};

// stack for maintaining
class LRUStack {
public:
    LRUStack();
    void Push(int p, int a);
    LRU* Pop(int pid, int alloc);
    LRU* GetLeastUsed();

    LRU* GetTail();
    LRU* GetHead();
    int GetSize();
    bool IsEmpty();
private:
    LRU *head, *tail;
    int size;
};
#endif
