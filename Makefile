all:
	g++ -Wall Graph.cpp -o graph-tests
	g++ -Wall BetterPriorityQueue.cpp -o bpq-tests
run: 
	./graph-tests
	./bpq-tests
try: all run