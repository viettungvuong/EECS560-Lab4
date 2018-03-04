#include "TwoThreeNode.h"
#include "TwoThreeTree.h"
#include "Queue.h"
#include <iostream>

TwoThreeTree::TwoThreeTree(){
  this->root = nullptr;
}
TwoThreeTree::~TwoThreeTree(){
  if(this->root != nullptr) recDestroy(this->root);
}
//destroy all of a node's children, then destroy it.
void TwoThreeTree::recDestroy(TwoThreeNode* curr){
  if (curr->third != nullptr) recDestroy(curr->third);
  if (curr->second != nullptr) recDestroy(curr->second);
  if (curr->first != nullptr) recDestroy(curr->first);
  delete curr;
}
//return a node if it exists.
TwoThreeNode* TwoThreeTree::find(int x){
  if(this->root == nullptr) return nullptr;
  return find(x, this->root);
}
//return a node if it exists in the subtree rooted at curr.
TwoThreeNode* TwoThreeTree::find(int x, TwoThreeNode* curr){
  if(curr->tag &&curr->val==x) return curr;
  if(curr->tag) return nullptr;
  if(x>=curr->minThird && curr->minThird != -1){
    return find(x, curr->third);
  }
  if(x>=curr->minSecond && curr->minSecond != -1){
    return find(x, curr->second);
  }
  return find(x, curr->first);
}


//return the minimum value, or -1 if not found.
int TwoThreeTree::findMin(){
  if (root == nullptr) return -1;
  return findMin(this->root);
}
//recursively find the minimum value of any subtree.
int TwoThreeTree::findMin(TwoThreeNode* curr){
  if (curr == nullptr) return -1;
  if (curr->first == nullptr) return curr->val;
  return findMin(curr->first);
}

//return the maximum value, or -1 if not found.
int TwoThreeTree::findMax(){
  if (root == nullptr) return -1;
  return findMax(this->root);
}
//recursively find the maximum value of any subtree.
int TwoThreeTree::findMax(TwoThreeNode* curr){
  if (curr->tag) return curr->val;
  if(curr->third != nullptr) return findMax(curr->third);
  if(curr->second != nullptr) return findMax(curr->second);
  return -1;
}


//Insert a value. Handle base cases and recurse for general cases.
void TwoThreeTree::insert(int x){
  if(find(x) != nullptr) return;
  //0 nodes
  if (this->root == nullptr){
    TwoThreeNode* newRoot = new TwoThreeNode(x, true, this->root);
    this->root = newRoot;
  }
  //one node
  else if(this->root->tag){
    TwoThreeNode* newIntern = new TwoThreeNode(-1, false, nullptr);
    TwoThreeNode* newLeaf = new TwoThreeNode(x, true, newIntern);
    if(x<this->root->val){
      addChild(newIntern, 1, newLeaf);
      addChild(newIntern, 2, this->root);
      newIntern->minSecond = this->root->val;
    }
    else{
      addChild(newIntern, 1, this->root);
      addChild(newIntern, 2, newLeaf);
      newIntern->minSecond = x;
    }
    this->root = newIntern;
    this->root->parent = newIntern;    
  }
  else{
    insertRec(x, this->root);
  }
}
//Insert a value recursively and adjust the tree.
void TwoThreeTree::insertRec(int x, TwoThreeNode* curr){
  bool firstFull = false;
  bool secondFull = false;
  bool thirdFull = false;
  if(curr->first != nullptr){
    firstFull = curr->first->tag;
  }
  if(curr->second != nullptr){
    secondFull = curr->second->tag;
  }
  if(curr->third != nullptr){
    thirdFull = curr->third->tag;
  }
  int count = 0;
  if (firstFull) count++;
  if (secondFull) count++;
  if (thirdFull) count++;
  bool spotFoundTwoChildren = ((count==2)&&(curr->tag==false));
  bool spotFoundThreeChildren = ((count==3)&&(curr->tag==false));
  //insert as child of non-full internal node and shift other children into place.
  if(spotFoundTwoChildren){
    //first - may decrease minimum of ancestors
    if(x<curr->first->val){

      TwoThreeNode* tmpOne = curr->first;
      TwoThreeNode* tmpTwo = curr->second;
      addChild(curr, 1, new TwoThreeNode(x, true, curr));
      addChild(curr, 2, tmpOne);
      addChild(curr, 3, tmpTwo);

      curr->minSecond = tmpOne->val;
      curr->minThird = tmpTwo->val;
    }
    //second
    else if (x<curr->minSecond){
      TwoThreeNode* tmp = curr->second;
      addChild(curr, 3, tmp);
      addChild(curr, 2, new TwoThreeNode(x, true, curr));
      curr->minSecond = x;
      curr->minThird = tmp->val;
    }
    //third
    else{
      addChild(curr, 3, new TwoThreeNode(x, true, curr));
      curr->minThird = x;
    }
    curr->parent->minSecond = findMin(curr->parent->second);
    curr->parent->minThird = findMin(curr->parent->third);

  }
  //split into two 2-nodes with 4 children total
  //gives us 'another spot to put it'
  else if (spotFoundThreeChildren){
    TwoThreeNode* newNode = new TwoThreeNode(-1, false, curr->parent);    
    //add as first
    if(x<curr->first->val){
      addChild(newNode, 1, curr->second);
      addChild(newNode, 2, curr->third);
      curr->second = nullptr;
      newNode->minSecond = curr->third->val;
      curr->third = nullptr;      
      TwoThreeNode* tmp = curr->first;
      addChild(curr, 1 , new TwoThreeNode(x, true, curr));
      addChild(curr, 2, tmp);
      curr->minSecond = tmp->val;

    }
    //add as second
    else if(x>curr->first->val && x<curr->minSecond){
      addChild(newNode, 2, curr->third);
      newNode->minSecond = curr->third->val;
      curr->third = nullptr;
      addChild(newNode, 1, curr->second);
      curr->second = nullptr;
      addChild(curr, 2, new TwoThreeNode(x, true, curr));
    }
    //add as first of new node
    else if(x>curr->minSecond && x<curr->minThird){
      addChild(newNode, 1, new TwoThreeNode(x, true, curr));
      addChild(newNode, 2, curr->third);
      curr->third = nullptr;

    }
    //add as second of new node
    else{
      addChild(newNode, 1, curr->third);
      addChild(newNode, 2, new TwoThreeNode(x, true, curr));
      curr->third = nullptr;
    }
    curr->minSecond = findMin(curr->second);
    curr->minThird = -1;

    newNode->minSecond = findMin(newNode->second);
    newNode->minThird = -1;
    split(curr, newNode);
  }
  //not yet to leaves
  //recurse on first
  else if (x<curr->minSecond){
    insertRec(x, curr->first);
  }
  //recurse on second
  else if (x<curr->minThird){
    insertRec(x, curr->second);
  }
  //recurse on third
  else{
    insertRec(x, curr->third);
  } 

}
//Add two split nodes to the tree.
void TwoThreeTree::split(TwoThreeNode* curr, TwoThreeNode* newNode){
  //make a new root to host the split nodes
  if (curr==this->root){
    TwoThreeNode* newRoot = new TwoThreeNode(-1, false, this->root);
    addChild(newRoot, 1, curr);
    addChild(newRoot, 2, newNode);
    newRoot->minSecond = findMin(newRoot->second);
    this->root = newRoot;
  }
  else{
    TwoThreeNode* par = curr->parent;
    int count = numChildren(par);
    bool twoChildren = ((count==2)&&(par->tag==false));
    bool threeChildren = ((count==3)&&(par->tag==false));
    //attach the split-off node to the original node's parent
    if(twoChildren){
      if(par->first == curr){
        addChild(par, 3, par->second);
        addChild(par, 2, newNode);
      }
      else{
        addChild(par, 3, newNode);
      }
      par->minSecond = findMin(par->second);
      par->minThird = findMin(par->third);
    }
    //split recursively
    else if (threeChildren){
      TwoThreeNode* newIntern = new TwoThreeNode(-1, false, nullptr);
      if(par->first == curr){
        addChild(newIntern, 1, par->second);
        addChild(newIntern, 2, par->third);
        addChild(par, 2, newNode);
        par->third = nullptr;
      }
      else if (par->second == curr){
        addChild(newIntern, 1, newNode);    
        addChild(newIntern, 2, par->third);
        par->third = nullptr;
      }
      else{
        addChild(newIntern, 1, par->third);    
        addChild(newIntern, 2, newNode);
      }
      par->minSecond = findMin(par->second);
      par->minThird = -1;

      newIntern->minSecond = findMin(newIntern->second);
      newIntern->minThird = -1;
      split(par, newIntern);    
    }
  }
}
//Find a specific number and delete it. Return true if deleted or false if not found.
bool TwoThreeTree::Delete(int x){
  TwoThreeNode* target = find(x);
  if(target == nullptr){
    return false;
  }
  else{
    return Delete(target);
  }
}
//Delete a specific node and correct the tree.
bool TwoThreeTree::Delete(TwoThreeNode* x){
  //x is root
  if(x==this->root){
    delete x;
    this->root = nullptr;
  }
  else{
    TwoThreeNode* par = x->parent;
    int count = numChildren(par);
    bool twoChildren = ((count==2)&&(par->tag==false));
    bool threeChildren = ((count==3)&&(par->tag==false));
    //x's parent has two children
    if(twoChildren){
      //x's parent is root
      if(par == (this->root)){
        TwoThreeNode* tmp = par;
        //x is first child of root
        if(par->first == x){
          this->root = par->second;
          delete x;
          delete tmp;
          
        }
        //x is second child of root
        else{
          this->root = par->first;
          delete x;
          delete tmp;
        }
      }
      //not root
      else{
        TwoThreeNode* par2 = par->parent;
        TwoThreeNode* parSib;
        if(numChildren(par2->first) == 3 && par2->second == par){
          parSib = par2->first;
          if(par->second ==x){
            addChild(par, 2, par->first);
          }
          addChild(par, 1, parSib->third);
          parSib->minThird = -1;
          parSib->third = nullptr;
        }
        else if (numChildren(par2->second) == 3 && (par==par2->first || par==par2->third)){
          parSib = par2->second;
          if(par2->first == par){
            if(par->first == x) addChild (par, 1, par->second);
            addChild(par, 2, parSib->first);
            addChild(parSib, 1, parSib->second);
            addChild(parSib, 2, parSib->third);
            parSib->minThird = -1;
            parSib->third = nullptr;
          }
          else{
            if(par->second == x) addChild(par, 2, par->first);
            addChild(par, 1, parSib->third);
            parSib->minThird = -1;
            parSib->third = nullptr;
          }
        }
        else if (numChildren(par2->third) == 3 && par == par2->second){
          parSib = par2->third;
          if(par->first == x) addChild (par, 1, par->second);
          addChild(par, 2, parSib->first);
          addChild(parSib, 1, parSib->second);
          addChild(parSib, 2, parSib->third);
          parSib->minThird = -1;
          parSib->third = nullptr;
        }
        else{
          TwoThreeNode* xSib;
          if(x==par->first){
            xSib = par->second;
          }
          else xSib = par->first;
          if(par2->first == par){
            parSib = par2->second;
            addChild(parSib, 3, parSib->second);
            addChild(parSib, 2, parSib->first);
            addChild(parSib, 1, xSib);
          }
          else if(par2->second == par){
            parSib = par2->first;
            if(numChildren(parSib) != 3) addChild(parSib, 3, xSib);
            else{
              parSib = par2->third;
              addChild(parSib, 3, parSib->second);
              addChild(parSib, 2, parSib->first);
              addChild(parSib, 1, xSib);
            }
          }
          else{
            parSib = par2->second;
            addChild(parSib, 3, xSib);
          }
          delete x;
          Delete(par);
        }
      }
    }
    //x's parent has three children
    //cases for x being first, second, or third
    else if (threeChildren){
      if(par->first == x){
        delete x;
        par->first = par->second;
        par->second = par->third;
        par->third = nullptr;
        par->minSecond = par->minThird;
        par->minThird = -1;
      }
      else if (par->second ==x){
        delete x;
        par->second = par->third;
        par->third = nullptr;
        par->minSecond = par->minThird;
        par->minThird = -1;
      }
      else{
        delete x;
        par->third = nullptr;
        par->minThird = -1;
      }
    }
    recUpdateAllMins(this->root);
  }
  return true;
}
//Recursively fix minimum values for all internal nodes.
void TwoThreeTree::recUpdateAllMins(TwoThreeNode* curr){
  if(curr!=nullptr && !curr->tag){
    recUpdateAllMins(curr->first);
    if(curr->second != nullptr){
      recUpdateAllMins(curr->second);
      curr->minSecond = findMin(curr->second);
    }
    else curr->minSecond = -1;

    if(curr->third != nullptr){
      recUpdateAllMins(curr->third);
      curr->minThird = findMin(curr->third);
    }
    else curr->minThird = -1;
  }
}
//Get the number of children of a node.
//Returns 0 if the node is null.
int TwoThreeTree::numChildren(TwoThreeNode* x){
  if(x==nullptr) return 0;
  bool firstFull = false;
  bool secondFull = false;
  bool thirdFull = false;
  if(x->first != nullptr){
    firstFull = true;
  }
  if(x->second != nullptr){
    secondFull = true;
  }
  if(x->third != nullptr){
    thirdFull = true;
  }
  int count = 0;
  if (firstFull) count++;
  if (secondFull) count++;
  if (thirdFull) count++;
  return count;
}

//add child and set parent automatically
void TwoThreeTree::addChild(TwoThreeNode* par, int pos, TwoThreeNode* child){
  if (pos ==1){
    par->first = child;
  }
  else if (pos ==2){
    par->second = child;
  }
  else if (pos ==3){
    par->third = child;
  }
  child->parent = par;
}
//delete the maximum and return it or -1 if not present.
int TwoThreeTree::deleteMax(){
  int target = findMax();
  if (target == -1) return -1;
  Delete(target);
  return target;
}
//delete the minimum and return it or -1 if not present
int TwoThreeTree::deleteMin(){
  int target = findMin();
  if (target == -1) return -1;
  Delete(target);
  return target;
}
//using a queue, print the leaves in order.
void TwoThreeTree::levelOrder(){
  Queue* q = new Queue();
  if(this->root != nullptr){
    std::cout << "Level order: ";
    q->enqueue(this->root);
    TwoThreeNode* curr;
    while(!q->isEmpty()){
      //put all of a node's children on the queue before popping it
      curr = q->peek();
      if(curr->tag){
        std::cout << curr->val << " ";
      }
      if(curr->first != nullptr){
        q->enqueue(curr->first);
      }
      if(curr->second != nullptr){
        q->enqueue(curr->second);
      }
      if(curr->third != nullptr){
        q->enqueue(curr->third);
      }
      q->dequeue();
    }
    std::cout <<"\n";
  }
}
