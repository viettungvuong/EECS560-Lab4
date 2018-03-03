#ifndef TTNODE
#define TTNODE

class TwoThreeNode{
public:
  TwoThreeNode(int x, bool flag, TwoThreeNode* parent);
  ~TwoThreeNode();
  int minSecond;
  int minThird;
  int val;
  bool tag; //true if leaf
  TwoThreeNode* parent;
  TwoThreeNode* first;
  TwoThreeNode* second;
  TwoThreeNode* third;
};
#endif