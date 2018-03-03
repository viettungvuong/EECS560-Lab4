prog: main.o TwoThreeTree.o TwoThreeNode.o Queue.o QueueNode.o
	g++ -g -Wall -std=c++11 main.o TwoThreeTree.o TwoThreeNode.o  Queue.o QueueNode.o -o prog

main.o: main.cpp
	g++ -g -Wall -std=c++11 -c main.cpp

TwoThreeTree.o: TwoThreeTree.cpp TwoThreeTree.h
	g++ -g -Wall -std=c++11 -c TwoThreeTree.cpp

TwoThreeNode.o: TwoThreeNode.cpp TwoThreeNode.h
		g++ -g -Wall -std=c++11 -c TwoThreeNode.cpp

Queue.o: Queue.cpp Queue.h
		g++ -g -Wall -std=c++11 -c Queue.cpp

QueueNode.o: QueueNode.cpp QueueNode.h
		g++ -g -Wall -std=c++11 -c QueueNode.cpp

clean:
	rm *.o prog
