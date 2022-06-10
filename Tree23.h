
struct Node23
{
  Node23(int x, bool flag, Node23 *parent);
  int size = 1;
  int x = -1;
  int y = -1;
  int val;
  bool leaf; // true if leaf
  Node23 *parent;
  Node23 *first = nullptr;
  Node23 *second = nullptr;
  Node23 *third = nullptr;
};
struct Tree23
{
  Node23 *root = nullptr;
  Tree23();
  void insert(int x);
  void insertRec(int x, Node23 *curr);
  void split(Node23 *curr, Node23 *newNode);
  int findMin();
  int findMin(Node23 *curr);
  int findMax();
  int findMax(Node23 *curr);
  void addChild(Node23 *par, int pos, Node23 *child);
  int numChildren(Node23 *x);
  void inorderTraverse(Node23 *curr, std::fstream &ofs);
};
Tree23 importFromFile();