#include <fstream>
#include <iostream>
#include "TwoThreeTree.h"

int main(){
    TwoThreeTree* tree = new TwoThreeTree();
    std::ifstream file;
    file.open("data.txt");
    int curr;
    while(file>>curr){
        tree->insert(curr);
    }
    bool going = true;
    int choice;
    std::cout << "Please choose one of the following commands:\n";
    std::cout << "1- Insert\n2- DeleteMin\n3- DeleteMax\n4- FindMin\n5- FindMax\n6- Find\n7- Delete\n8- Level Order\n9- Exit\n";
    while(going){
        switch(choice){
            case 1:
            case 2:
                tree.deleteMin();
                break;
            case 3:
                tree.deleteMax();
                break;
            case 4:
                tree.findMin();
                break;
            case 5:
                tree.findMax();
                break;
            case 6:
                tree.find();
                break;
            case 7:
                tree.delete();
            case 8:
                tree.levelOrder();
                break;
            case 9:
                going = false;
                break;
        }
    }
    return 0;
}