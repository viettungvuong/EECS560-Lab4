#import "TwoThreeNode.h"

TwoThreeTree::TwoThreeTree(){
  this->root = nullptr;
}
TwoThreeTree::~TwoThreeTree(){
  if(this->root != nullptr) recDestroy(this->root);
}
void TwoThreeTree::recDestroy(TwoThreeNode* curr){
  if (curr->third != nullptr) recDestroy(curr->third);
  if (curr->second != nullptr) recDestroy(curr->second);
  if (curr->first != nullptr) recDestroy(curr->first);
  delete curr;
}

TwoThreeNode* TwoThreeTree::find(int x){
  if(this->root == nullptr) return nullptr;
  return find(x, this->root);
}
TwoThreeNodee* TwoThreeTree::find(int x, TwoThreeNode* curr){
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



int TwoThreeTree::findMin(){
  if (root == nullptr) return -1;
  return findMin(this->root);
}
int TwoThreeTree::findMin(TwoThreeNode* curr){
  if (curr == nullptr) return -1;
  if (curr->first == nullptr) return curr->val;
  return findMin(curr->first);
}

TwoThreeNode* TwoThreeTree::findMinNode(){
  if (root == nullptr) return nullptr;
  return findMinNode(this->root);
}
TwoThreeNode* TwoThreeTree::findMinNode(TwoThreeNode* curr){
  if (curr == nullptr) return -1;
  if (curr->first == nullptr) return curr;
  return findMinNode(curr->first);
}



int TwoThreeTree::findMax(){
  if (root == nullptr) return -1;
  return findMax(this->root);
}
int TwoThreeTree::findMax(TwoThreeNode* curr){
  if (curr->tag) return curr->val;
  if(curr->third != nullptr) return findMax(curr->third);
  if(curr->second != nullptr) return findMax(curr->second);
}

TwoThreeNode* TwoThreeTree::findMaxNode(){
  if (root == nullptr) return nullptr;
  return findMaxNode(this->root);
}
TwoThreeNode* TwoThreeTree::findMaxNode(TwoThreeNode* curr){
  if (curr->tag) return curr;
  if (curr->third != nullptr) return findMaxNode(curr->third);
  if (curr->second != nullptr) return findMaxNode(curr->second);
}




void TwoThreeTree::insert(int x){
  //0 nodes
  if (this->root == nullptr){
    TwoThreeNode* newRoot = new TwoThreeNode(x, true, this->root);
    this->root = newRoot;
    return;
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
    
void TwoThreeTree::insertRec(int x, TwoThreeNode* curr){
  bool firstFull = (curr->first != nullptr && curr->first->tag == true);
  bool secondFull = (curr->second != nullptr && curr->second->tag == true);
  bool thirdFull = (curr->third != nullptr && curr->third->tag == true);
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
      addChild(curr, third, new TwoThreeNode(x, true, curr));
      curr->minThird = x;
    }
    curr->parent->minSecond = findMin(curr->parent->second);
    curr->parent->minThird = findMin(curr->parent->third);

  }
  //split into two 2-nodes
  else if (spotFoundThreeChildren){
    TwoThreeNode* newNode = new TwoThreeNode(-1, false, curr->parent);    
    //add as first
    if(x<curr->first->val){
      addChild(newNode, 1, curr->second);
      addChild(newNode, 2, curr->third);
      curr->second = nullptr;
      curr->third = nullptr;
      newNode->minSecond = curr->third->val;
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
void TwoThreeTree::split(TwoThreeNode* curr, TwoThreeNode* newNode){
  if (curr==this->root){
    TwoThreeNode* newRoot = new TwoThreeNode(-1, false, this->root);
    addChild(newRoot, 1, curr);
    addChild(newRoot, 2, newNode);
    newRoot->minSecond = findMin(newRoot->second);
    this->root = newRoot;
  }
  else{
    TwoThreeNode* par = curr->parent;
    bool firstFull = (par->first != nullptr && par->first->tag == true);
    bool secondFull = (par->second != nullptr && par->second->tag == true);
    bool thirdFull = (par->third != nullptr && par->third->tag == true);
    int count = 0;
    if (firstFull) count++;
    if (secondFull) count++;
    if (thirdFull) count++;
    bool twoChildren = ((count==2)&&(par->tag==false));
    bool threeChildren = ((count==3)&&(par->tag==false));
    if(twoChildren){
      if(par->first = curr){
        addChild(par, 3, par->second);
        addChild(par, 2, newNode);
      }
      else{
        addChild(par, 3, newNode);
      }
      par->minSecond = findMin(par->second);
      par->minThird = findMin(par->third);
    }
    else if (threeChildren){
      TwoThreeNode* newIntern = new TwoThreeNode(-f, false, );
      if(par->first == curr){
        addChild(newIntern, 1, par->second);
        addChild(newIntern, 2, par->third);
        addChild(par, 2, newNode);
        par->third = nullptr;
      }
      else if (par->second = curr){
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
void TwoThreeTree::Delete(int x){
  
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

