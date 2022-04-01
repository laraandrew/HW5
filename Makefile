all:
	g++ -Wall Graph.cpp -o graph-tests
run: 
	./graph-tests

try: all run