#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"
// node used for process
struct Node {
    Process *p;
    Node *next;
};

// Queue used for runQueue, ioQueue, sleepQueue
class Queue {
public:
    Queue();
    void Enqueue(Process *p);
    Process* Dequeue(int pid);
    Process* Dequeue();

    Node* GetHead();
    int GetSize();
    bool IsEmpty();
private:
    Node *head, *tail;
    int size;
};
#endif
