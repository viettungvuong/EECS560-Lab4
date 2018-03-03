#include "Queue.h"
Queue::Queue(){
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}
Queue::~Queue(){
    while(!isEmpty()){
        dequeue();
    }
}

void Queue::enqueue(TwoThreeNode* x){
    QueueNode* newNode = new QueueNode(x, nullptr);
    if(isEmpty()){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->setNext(newNode);
        tail = newNode;
    }
    this->count++;
}
void Queue::dequeue(){
    if(!isEmpty()){
        QueueNode* tmp = head;
        head = tmp->getNext();

        delete tmp;
        this->count--;
    }
}
TwoThreeNode* Queue::peek(){
    return head->getVal();
}

bool Queue::isEmpty(){
    return (this->count == 0);
}