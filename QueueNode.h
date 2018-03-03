#ifndef QNODE
#define QNODE
#include "TwoThreeNode.h"

class QueueNode{
private:
    TwoThreeNode* val;
    QueueNode* next;
public:
    QueueNode();
    QueueNode(TwoThreeNode* val, QueueNode* next);
    TwoThreeNode* getVal();
    QueueNode* getNext();
    void setNext(QueueNode* newNext);
};

#endif QNODE