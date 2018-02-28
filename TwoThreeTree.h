#ifndef TTTree
#define TTTree
class TwoThreeTree{
public:
  TwoThreeTree();
  ~TwoThreeTree();
  void insert(int x);
  bool Delete(int x);
  void deleteMin();
  void deleteMax();
  int findMin();
  int findMax();
  bool find(int x);
  void levelOrder(); //implement queue
private:
  TwoThreeNode* root;
}