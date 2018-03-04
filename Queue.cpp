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
//Add a TwoThreeNode to the back of the queue.
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
//Remove the TwoThreeNode at the front of the queue.
void Queue::dequeue(){
    if(!isEmpty()){
        QueueNode* tmp = head;
        head = tmp->getNext();

        delete tmp;
        this->count--;
    }
}
//Get the value at the front of the queue
TwoThreeNode* Queue::peek(){
    return head->getVal();
}
//Return whether the queue is empty.
bool Queue::isEmpty(){
    return (this->count == 0);
}