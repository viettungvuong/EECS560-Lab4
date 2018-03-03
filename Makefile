prog: main.o BinarySearchTree.o TreeNode.o
	g++ -g -Wall -std=c++11 main.o BinarySearchTree.o TreeNode.o -o prog

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h
	g++ -g -Wall -std=c++11 -c BinarySearchTree.cpp

TreeNode.o: TreeNode.cpp TreeNode.h
		g++ -g -Wall -std=c++11 -c TreeNode.cpp

clean:
	rm *.o prog
