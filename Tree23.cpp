#include "Tree23.h"
#include <iostream>
#include <fstream>
Node23::Node23(int x, bool flag, Node23 *parent)
{
  this->leaf = flag;
  this->val = x;
  this->parent = parent;
}
int Tree23::findMin()
{
  if (root)
    return -1;
  return findMin(this->root);
}
int Tree23::findMin(Node23 *curr)
{
  if (curr)
    return -1;
  if (curr->first)
    return curr->val;
  return findMin(curr->first);
}

int Tree23::findMax()
{
  if (root)
    return -1;
  return findMax(this->root);
}
int Tree23::findMax(Node23 *curr)
{
  if (curr->leaf)
    return curr->val;
  if (curr->third != nullptr)
    return findMax(curr->third);
  if (curr->second != nullptr)
    return findMax(curr->second);
  return -1;
}
void Tree23::insert(int x)
{
  // 0 nodes
  if (!this->root)
  {
    Node23 *newRoot = new Node23(x, true, this->root);
    this->root = newRoot;
  }
  // one node
  else if (this->root->leaf)
  {
    Node23 *newIntern = new Node23(-1, false, nullptr);
    Node23 *newLeaf = new Node23(x, true, newIntern);
    if (x < this->root->val)
    {
      addChild(newIntern, 1, newLeaf);
      addChild(newIntern, 2, this->root);
      newIntern->x = this->root->val;
    }
    else
    {
      addChild(newIntern, 1, this->root);
      addChild(newIntern, 2, newLeaf);
      newIntern->x = x;
    }
    this->root = newIntern;
    this->root->parent = newIntern;
  }
  else
  {
    insertRec(x, this->root);
  }
}
void Tree23::insertRec(int x, Node23 *curr)
{
  bool firstFull = false;
  bool secondFull = false;
  bool thirdFull = false;
  if (curr->first != nullptr)
  {
    firstFull = curr->first->leaf;
  }
  if (curr->second != nullptr)
  {
    secondFull = curr->second->leaf;
  }
  if (curr->third != nullptr)
  {
    thirdFull = curr->third->leaf;
  }
  int count = 0;
  if (firstFull)
    count++;
  if (secondFull)
    count++;
  if (thirdFull)
    count++;
  bool spotFoundTwoChildren = ((count == 2) && (curr->leaf == false));
  bool spotFoundThreeChildren = ((count == 3) && (curr->leaf == false));

  if (spotFoundTwoChildren)
  {
    // first - may decrease minimum of ancestors
    if (x < curr->first->val)
    {

      Node23 *tmpOne = curr->first;
      Node23 *tmpTwo = curr->second;
      addChild(curr, 1, new Node23(x, true, curr));
      addChild(curr, 2, tmpOne);
      addChild(curr, 3, tmpTwo);

      curr->x = tmpOne->val;
      curr->y = tmpTwo->val;
    }
    // second
    else if (x < curr->x)
    {
      Node23 *tmp = curr->second;
      addChild(curr, 3, tmp);
      addChild(curr, 2, new Node23(x, true, curr));
      curr->x = x;
      curr->y = tmp->val;
    }
    // third
    else
    {
      addChild(curr, 3, new Node23(x, true, curr));
      curr->y = x;
    }
    curr->parent->x = findMin(curr->parent->second);
    curr->parent->y = findMin(curr->parent->third);
  }
  else if (spotFoundThreeChildren)
  {
    Node23 *newNode = new Node23(-1, false, curr->parent);
    // add as first
    if (x < curr->first->val)
    {
      addChild(newNode, 1, curr->second);
      addChild(newNode, 2, curr->third);
      curr->second = nullptr;
      newNode->x = curr->third->val;
      curr->third = nullptr;
      Node23 *tmp = curr->first;
      addChild(curr, 1, new Node23(x, true, curr));
      addChild(curr, 2, tmp);
      curr->x = tmp->val;
    }
    // add as second
    else if (x > curr->first->val && x < curr->x)
    {
      addChild(newNode, 2, curr->third);
      newNode->x = curr->third->val;
      curr->third = nullptr;
      addChild(newNode, 1, curr->second);
      curr->second = nullptr;
      addChild(curr, 2, new Node23(x, true, curr));
    }
    // add as first of new node
    else if (x > curr->x && x < curr->y)
    {
      addChild(newNode, 1, new Node23(x, true, curr));
      addChild(newNode, 2, curr->third);
      curr->third = nullptr;
    }
    // add as second of new node
    else
    {
      addChild(newNode, 1, curr->third);
      addChild(newNode, 2, new Node23(x, true, curr));
      curr->third = nullptr;
    }
    curr->x = findMin(curr->second);
    curr->y = -1;

    newNode->x = findMin(newNode->second);
    newNode->y = -1;
    split(curr, newNode);
  }
  // not yet to leaves
  // recurse on first
  else if (x < curr->x)
  {
    insertRec(x, curr->first);
  }
  // recurse on second
  else if (x < curr->y)
  {
    insertRec(x, curr->second);
  }
  // recurse on third
  else
  {
    insertRec(x, curr->third);
  }
}
// Add two split nodes to the tree.
void Tree23::split(Node23 *curr, Node23 *newNode)
{
  // make a new root to host the split nodes
  if (curr == this->root)
  {
    Node23 *newRoot = new Node23(-1, false, this->root);
    addChild(newRoot, 1, curr);
    addChild(newRoot, 2, newNode);
    newRoot->x = findMin(newRoot->second);
    this->root = newRoot;
  }
  else
  {
    Node23 *par = curr->parent;
    int count = numChildren(par);
    bool twoChildren = ((count == 2) && (par->leaf == false));
    bool threeChildren = ((count == 3) && (par->leaf == false));
    // attach the split-off node to the original node's parent
    if (twoChildren)
    {
      if (par->first == curr)
      {
        addChild(par, 3, par->second);
        addChild(par, 2, newNode);
      }
      else
      {
        addChild(par, 3, newNode);
      }
      par->x = findMin(par->second);
      par->y = findMin(par->third);
    }
    // split recursively
    else if (threeChildren)
    {
      Node23 *newIntern = new Node23(-1, false, nullptr);
      if (par->first == curr)
      {
        addChild(newIntern, 1, par->second);
        addChild(newIntern, 2, par->third);
        addChild(par, 2, newNode);
        par->third = nullptr;
      }
      else if (par->second == curr)
      {
        addChild(newIntern, 1, newNode);
        addChild(newIntern, 2, par->third);
        par->third = nullptr;
      }
      else
      {
        addChild(newIntern, 1, par->third);
        addChild(newIntern, 2, newNode);
      }

      newIntern->x = findMin(newIntern->second);
      newIntern->y = -1;

      par->x = findMin(par->second);
      par->y = -1;

      split(par, newIntern);
    }
  }
}

void Tree23::addChild(Node23 *par, int pos, Node23 *child)
{
  if (pos != 1 && pos != 2 && pos != 3)
    return;
  if (pos == 1)
  {
    par->first = child;
  }
  else if (pos == 2)
  {
    par->second = child;
  }
  else if (pos == 3)
  {
    par->third = child;
  }
  child->parent = par;
}
void Tree23::inorderTraverse(Node23 *curr, std::fstream &ofs)
{
  if (!curr)
    return;
  if (curr->x != -1 && curr->y != -1) // 2 key
  {
    inorderTraverse(curr->first, ofs);
    ofs << curr->x << " ";
    inorderTraverse(curr->second, ofs);
    ofs << curr->y << " ";
    inorderTraverse(curr->third, ofs);
  }
  else
  {
    inorderTraverse(curr->first, ofs);
    ofs << curr->x << " ";
    inorderTraverse(curr->third, ofs);
  }
}
Tree23 importFromFile()
{
  Tree23 ans;
  std::fstream ifs;
  ifs.open("input.txt", std::ios::in);
  int in;
  while (!ifs.eof())
  {
    ifs >> in;
    ans.insert(in);
  }
  return ans;
}