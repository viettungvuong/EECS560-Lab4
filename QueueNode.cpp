#include "QueueNode.h"
QueueNode::QueueNode(TwoThreeNode* val, QueueNode* next){
    this->val = val;
    this->next = next;
}
TwoThreeNode* QueueNode::getVal(){
    return this->val;
}
QueueNode* QueueNode::getNext(){
    return this->next;
}
void QueueNode::setNext(QueueNode* newNext){
    this->next = newNext;
}
