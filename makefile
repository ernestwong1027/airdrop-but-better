all:
	g++ -Wall -c ./src/main.cpp
	g++ -Wall -c ./src/executeCommand.cpp                       
	g++ -Wall -c ./src/parseCommand.cpp                                                            
	g++ -Wall -c ./src/IO.cpp       
	g++ -Wall -c ./src/HuffmanEncoding.cpp  
	g++ -Wall -c ./src/HuffmanDecoding.cpp  
	g++ -Wall -c ./src/HuffmanNode.cpp         
	g++ -Wall -c ./src/PriorityQueue.cpp
	g++ -std=c++1y -L/usr/lib64/ -lboost_system -lboost_thread -Wall -c ./src/server.cpp 
	g++ main.o executeCommand.o parseCommand.o IO.o HuffmanEncoding.o HuffmanDecoding.o HuffmanNode.o PriorityQueue.o server.o -o main