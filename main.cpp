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
    while(going){
        std::cout << "Please choose one of the following commands:\n";
        std::cout << "1- Insert\n2- DeleteMin\n3- DeleteMax\n4- FindMin\n5- FindMax\n6- Find\n7- Delete\n8- Level Order\n9- Exit\n";
        std::cin >> choice;    
        switch(choice){
            case 1:
            {
                int insertVal;
                std::cout << "Choose a number to be inserted to the tree:";
                std::cin >> insertVal;
                tree->insert(insertVal);
                break;
            }
            case 2:
            {
                int delMinRes = tree->deleteMin();
                if(delMinRes ==-1){
                    std::cout << "Nothing to delete.\n";
                }
                else{
                    std::cout << delMinRes << " has been deleted from the tree.\n";
                }
                break;
            }
            case 3:
            {
                int delMaxRes = tree->deleteMax();
                if(delMaxRes ==-1){
                    std::cout << "Nothing to delete.\n";
                }
                else{
                    std::cout << delMaxRes << " has been deleted from the tree.\n";
                }
                break;
            }
            case 4:
            {
                tree->findMin();
                break;
            }
            case 5:
            {
                tree->findMax();
                break;
            }
            case 6:
            {
                int findTarget;
                std::cout << "Enter a number to be found:";
                std::cin >> findTarget;
                TwoThreeNode* res = tree->find(findTarget);
                if(res != nullptr){
                    std::cout << findTarget << " exists in the tree\n";
                }
                else{
                    std::cout << findTarget << " does not exist in the tree\n";
                }
                break;
            }
            case 7:
            {
                int delTarget;            
                std::cout << "Choose a number to be deleted from the tree:";
                std::cin >> delTarget;
                bool succ = tree->Delete(delTarget);
                if(succ) std::cout << delTarget << " has been deleted from the tree\n";
                else std::cout << delTarget << " could not be deleted.\n";
                break;
            }
            case 8:
            {
                tree->levelOrder();
                break;
            }
            case 9:
            {
                going = false;
                break;
            }
        }
    }
    return 0;
}