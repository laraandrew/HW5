all:
	g++ -Wall BetterPriorityQueue.cpp -o bpq-tests
run: 
	./bpq-tests
	
try: all run