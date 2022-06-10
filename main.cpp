#include <fstream>
#include <iostream>
#include "Tree23.h"

using namespace std;

int main()
{
    Tree23 tree = importFromFile();
    fstream ofs;
    ofs.open("output.txt", std::ios::out);
    tree.inorderTraverse(tree.root, ofs);
    cout << "Hello";
    return 0;
}