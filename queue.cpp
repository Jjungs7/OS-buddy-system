#include "queue.h"
#include "process.h"
#include "stack.h"
#include <cstdio>

Queue::Queue() : size(0) {
    head = NULL;
    tail = NULL;
}

// enqueues one process to tail
void Queue::Enqueue(Process *p) {
    Node *newNode = new Node;
    newNode->next = NULL;
    newNode->p = p;
    size++;
    if(head != NULL) {
        tail->next = newNode;
        tail = tail->next;
    } else {
        head = newNode;
        tail = newNode;
    }
}

// dequeues process with a specific pid
Process* Queue::Dequeue(int pid) {
    Node *parent;
    Node *current = head;

    bool pExists = false;
    while(current != NULL) {
        if(current->p->GetPid() == pid) {
            pExists = true;
            break;
        }
        parent = current;
        current = current->next;
    }

    if(pExists) {
        Process *p = current->p;
        if(current == head) {
            Node *t = head;
            head = head->next;
            delete t;
        } else if(current == tail) {
            tail = parent;
            tail->next = NULL;
            delete current;
        } else {
            parent->next = current->next;
            delete current;
        }

        size--;
        return p;

    } else {
        printf("Error while dequeing process\n");
        return NULL;
    }
}

// dequeues head process
Process* Queue::Dequeue() {
    if(size == 1) {
        Process *p = head->p;
        delete head;
        head = NULL;
        tail = NULL;
        size--;
        return p;
    } else if(size > 1) {
        Process *p = head->p;
        Node *current = head;
        head = head->next;
        delete current;
        size--;
        return p;
    }

    return NULL;
}

Node* Queue::GetHead() { return head; }
int Queue::GetSize() { return size; } 
bool Queue::IsEmpty() { return size == 0; }


// LRUStack data structure for LRU
LRUStack::LRUStack() : size(0) {
    head = NULL;
    tail = NULL;
}

// pushes on top of the stack
void LRUStack::Push(int p, int a) {
    LRU *n = new LRU();
    n->pid = p;
    n->allocId = a;
    n->prev = NULL;
    if(size == 0) {
        n->next = NULL;
        n->prev = NULL;
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    size++;
}

// pops specific memory pid & allocid
LRU* LRUStack::Pop(int pid, int alloc) {
    if(size > 0) {
        LRU *parent;
        LRU *current = head;
        while(current != NULL) {
            if((current->pid == pid) && (current->allocId == alloc)) {
                break;
            }
            parent = current;
            current = current->next;
        }

        size--;
        if(size == 0) {
            head = NULL;
            tail = NULL;
            current->next = NULL;
            current->prev = NULL;
            return current;
        } else {
            if(current == head) {
                LRU *temp = current;
                current = current->next;
                current->prev = NULL;
                temp->next = NULL;
                head = current;
                return temp;
            } else if(current == tail) {
                parent->next = NULL;
                current->prev = NULL;
                tail = parent;
                return current;
            } else {
                current->next->prev = parent;
                parent->next = current->next;
                current->next = NULL;
                current->prev = NULL;
                return current;
            }
        }
    }

    return NULL;
}

// pops tail and returns tail pid and allocid
LRU* LRUStack::GetLeastUsed() {
    return Pop(tail->pid, tail->allocId);
}

LRU* LRUStack::GetTail() { return tail; }
LRU* LRUStack::GetHead() { return head; }
int LRUStack::GetSize() { return size; }
bool LRUStack::IsEmpty() { return size == 0; }
