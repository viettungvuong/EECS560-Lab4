TwoThreeNode::TwoThreeNode(int x, bool flag, TwoThreeNode* parent){
  this->flag = flag;
  this->key = x;
  this->minSecond = -1;
  this->minThird = -1;
  this->parent = parent;
}