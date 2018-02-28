TwoThreeTree::TwoThreeTree(){

}
TwoThreeTree::~TwoThreeTree(){

}
void TwoThreeTree::insert(int x){
  //0 nodes
  if (this->root == nullptr){
    TwoThreeNode* newRoot = new TwoThreeNode(x, true, this->root);
    this->root = newRoot;
    return;
  }
  //one node
  else if(this->root->first == nullptr && this->root->second==nullptr && this->root->third==nullptr){
  {
    TwoThreeNode* newIntern = new TwoThreeNode(-1, false, nullptr);
    TwoThreeNode* newLeaf = new TwoThreeNode(x, true, newIntern);
    if(x<this->root->val){
      newIntern->second = newLeft;
      newIntern->third = this->root;
      newIntern->minSecond = x;
      newIntern->minThird = this->root->val;
    }
    else{
      newIntern->second = this->root;
      newIntern->third = newLeft;
      newIntern->minSecond = this->root->val;
      newIntern->minThird = x;
    }
    this->root->parent = newIntern;
    this->root = newIntern;
    newIntern->parent = this->root;
    return;
  }
  else insertRec(x, this->root);
  return;
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
    //first
    if(x<curr->first->val){
    }
    //second
    else if (x<curr->minSecond){
    }
    //third
    else{
    }

  }
  //split
  else if (spotFoundThreeChildren){
 
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

void TwoThreeTree::insertRec(int x, TwoThreeNode* curr){
  bool firstFull = (curr->first != nullptr && curr->first->tag == true);
  bool secondFull = (curr->second != nullptr && curr->second->tag == true);
  bool thirdFull = (curr->third != nullptr && curr->third->tag == true);

  if(curr->tag == false&&firstFull&&secondFull&&thirdFull){
    //split
    bool isRoot = (this->root == curr);
    TreeNode* newParent = nullptr;
    if (isRoot){
      newParent = new TwoThreeNode(-1, false, nullptr);
      this->root = newParent;
    }
    else{
      newParent = curr->parent;
    }
    TwoThreeNode* n1 = new TwoThreeNode(-1, false, newParent);
    n1->first = curr->first;
    n1->second = curr->second;
    TwoThreeNode* n2 = new TwoThreeNode(-1, false, newParent);
    n2->first = curr->third;
    insertRec(x, newParent);
  }

  else if(curr->minSecond == -1 && curr->minThird == -1){
    if(curr->first == nullptr){
      curr->first = new TwoThreeNode(x, curr, true);
    }
    else if (x>=curr->first->key){
      curr->second = new TwoThreeNode(x, curr, true);
      curr->minSecond = x;
    }
    else{
      curr->second = curr->first;
      curr->minSecond = findMin(curr->second);
      curr->first = new TwoThreeNode(x, curr, true);
    }
    return;
  }
  else if (curr->minThird ==-1){
    if(x>=curr->minSecond){
      curr->third = new TwoThreeNode(x, curr, true);
      curr->minThird = x;
    }
    else if (x<curr->minSecond){
      curr->third = curr->second
      curr->second = curr->first;
      curr->first = new TwoThreeNode(x, curr, true);
    }
  }

  else if(x<curr->minSecond){
    TwoThreeNode* first = curr->first;
    if (first == nullptr){
      TwoThreeNode* newNode = new TwoThreeNode(x, true, curr);
      curr->first = newNode;
      return;
    }
    insertRec(x, first);
  }
  else if (x<curr->minThird){
    if(curr->second == nullptr){
      TwoThreeNode* newNode = new TwoThreeNode(x, true, curr);
      curr->second = newNode;
      return;
    }
    if(curr->third == nullptr)
    insertRec(x, curr->second);
  }
  else{
    if(curr->third == nullptr){
      TwoThreeNode* newNode = new TwoThreeNode(x, true, curr);
      curr->second = newNode;
      return;
    }
    insertRec(x, curr->third);
  }
}
