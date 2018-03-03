#ifndef TTTree
#define TTTree
#import "TwoThreeNode.h"

class TwoThreeTree{
public:
  TwoThreeTree();
  ~TwoThreeTree();
  void insert(int x);
  void split(TwoThreeNode* curr, TwoThreeNode* newNode);
  bool Delete(int x);
  void deleteMin();
  void deleteMax();
  int findMin();
  int findMax();
  bool find(int x);
  void levelOrder(); //implement queue
  void addChild(TwoThreeNode* par, int pos, TwoThreeNode* child);

private:
  TwoThreeNode* root;
}