all:
	g++ -Wall -c ./src/main.cpp
	g++ -Wall -c ./src/executeCommand.cpp                       
	g++ -Wall -c ./src/parseCommand.cpp                                                            
	g++ -Wall -c ./src/IO.cpp       
	g++ -Wall -c ./src/HuffmanEncoding.cpp  
	g++ -Wall -c ./src/HuffmanNode.cpp         
	g++ -Wall -c ./src/PriorityQueue.cpp
	g++ main.o executeCommand.o parseCommand.o IO.o HuffmanEncoding.o HuffmanNode.o PriorityQueue.o -o main