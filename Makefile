all:
	g++ -Wall Graph.cpp GraphTests.cpp -o graph-tests
	g++ -Wall BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests
run: 
	./graph-tests
	./bpq-tests
try: all run