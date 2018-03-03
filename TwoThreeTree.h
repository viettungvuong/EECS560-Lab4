#ifndef TTTREE
#define TTTREE
#include "TwoThreeNode.h"

class TwoThreeTree{
public:
  TwoThreeTree();
  ~TwoThreeTree();
  void recDestroy(TwoThreeNode* curr);
  void insert(int x);
  void insert(int x, TwoThreeNode* curr);
  void split(TwoThreeNode* curr, TwoThreeNode* newNode);
  bool Delete(int x);
  int deleteMin();
  int deleteMax();
  int findMin();
  int findMin(TwoThreeNode* curr);
  int findMax();
  int findMax(TwoThreeNode* curr);
  TwoThreeNode* findMinNode();
  TwoThreeNode* findMinNode(TwoThreeNode* curr);
  TwoThreeNode* findMaxNode();
  TwoThreeNode* findMaxNode(TwoThreeNode* curr);
  TwoThreeNode* find(int x);
  TwoThreeNode* find(int x, TwoThreeNode* curr);
  void levelOrder(); //implement queue
  void addChild(TwoThreeNode* par, int pos, TwoThreeNode* child);

private:
  TwoThreeNode* root;
};
#endif