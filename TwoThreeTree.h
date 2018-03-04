#ifndef TTTREE
#define TTTREE
#include "TwoThreeNode.h"

class TwoThreeTree{
public:
  TwoThreeTree();
  ~TwoThreeTree();
  void recDestroy(TwoThreeNode* curr);
  void insert(int x);
  void insertRec(int x, TwoThreeNode* curr);
  void split(TwoThreeNode* curr, TwoThreeNode* newNode);
  bool Delete(int x);
  bool Delete(TwoThreeNode* x);
  int deleteMin();
  int deleteMax();
  int findMin();
  int findMin(TwoThreeNode* curr);
  int findMax();
  int findMax(TwoThreeNode* curr);
  TwoThreeNode* find(int x);
  TwoThreeNode* find(int x, TwoThreeNode* curr);
  void levelOrder(); //implement queue
  void recUpdateAllMins(TwoThreeNode* curr);
  void addChild(TwoThreeNode* par, int pos, TwoThreeNode* child);
  int numLeafChildren(TwoThreeNode* x);
private:
  TwoThreeNode* root;
};
#endif