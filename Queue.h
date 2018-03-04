#ifndef QUEUE
#define QUEUE

#include "QueueNode.h"

class Queue{
private:
    QueueNode* head;
    QueueNode* tail;
    int count;
public:
    Queue();
    ~Queue();

    bool isEmpty();
    void enqueue(TwoThreeNode* x);
    void dequeue();
    TwoThreeNode* peek();

};
#endif