#include "TwoThreeNode.h"
//construct node.
TwoThreeNode::TwoThreeNode(int x, bool flag, TwoThreeNode* parent){
  this->tag = flag;
  this->val = x;
  this->minSecond = -1;
  this->minThird = -1;
  this->first = nullptr;
  this->second = nullptr;
  this->third = nullptr;
  this->parent = parent;
}
TwoThreeNode::~TwoThreeNode(){

}