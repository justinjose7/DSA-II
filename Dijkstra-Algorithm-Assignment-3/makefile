main.exe: main.o  graph.o heap.o hash.o
	g++ main.o graph.o heap.o hash.o -o main

hash.o: hash.cpp
	g++ -c hash.cpp

heap.o: heap.cpp
	g++ -c heap.cpp

graph.o: graph.cpp
	g++ -c graph.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o main