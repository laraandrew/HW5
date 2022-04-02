#include "Graph.h"
#include "BetterPriorityQueue.h"
#include <iostream>
#include <climits>
#include <cassert>
#include "DNode.cpp"

using namespace std;

int dijkstra(const GraphNode *start, const GraphNode *end, Graph *g){
	vector<GraphNode*> vectNode;
	BetterPriorityQueue MinHeap;

	if (start == end){
		cout << "(" << end->key << ": 0)" << endl;
		return 0;
	}
	
	vectNode = g->GetNodes();

	DNode head;
	head.node = start;
	head.pri = 0;
	MinHeap.push(head);

	for (unsigned int k = 0; k < vectNode.size(); k++){
		DNode n;
		n.node = vectNode.at(k);
		if (n.node != start){
			n.pri = INT_MAX;
			MinHeap.push(n);
		}
	}

	while(!MinHeap.empty()) {
		DNode currN = MinHeap.top();
		MinHeap.pop();
		currN.visited = true;
		if(currN.node == end) {
			cout << MinHeap.DnodeToString(currN) << endl; //
			return currN.pri;
		}
		vector<GraphEdge*> edgeList = g->GetEdges(currN.node);
		for(unsigned int i = 0; i < edgeList.size(); i++) {
			DNode nextNode;
			GraphEdge *gEdge = edgeList.at(i);
			nextNode.node = gEdge->to;
			nextNode.pri = gEdge->weight + currN.pri;
			if(MinHeap.Contains(nextNode) && (nextNode.visited == false)) MinHeap.Update(nextNode);
		}
		cout << MinHeap.DnodeToString(currN) << endl;
	}
	return 0;
}


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	GraphNode *a = g->AddNode('1');
	GraphNode *b = g->AddNode('2');
	GraphNode *c = g->AddNode('3');
	GraphNode *d = g->AddNode('4');
	GraphNode *e = g->AddNode('5');
	GraphNode *f = g->AddNode('6');
	
	g->AddEdge(a, b, 7);
	g->AddEdge(b, a, 7);
	g->AddEdge(a, c, 9);
	g->AddEdge(c, a, 9);
	g->AddEdge(a, f, 14);
	g->AddEdge(f, a, 14);
	
	g->AddEdge(b, c, 10);
	g->AddEdge(c, b, 10);
	g->AddEdge(b, d, 15);
	g->AddEdge(d, b, 15);
	
	g->AddEdge(c, f, 2);
	g->AddEdge(f, c, 2);
	g->AddEdge(c, d, 11);
	g->AddEdge(d, c, 11);
	
	g->AddEdge(f, e, 9);
	g->AddEdge(e, f, 9);
	
	g->AddEdge(d, e, 6);
	g->AddEdge(e, d, 6);
	
	
	cout << g->ToString() << endl;
	
	int ans = dijkstra(g->NodeAt(0), g->NodeAt(g->Order()-2), g);
	assert(ans == 20);

	delete g;
	
	
	cout << "passed!" << endl;
	
	return ans;
}


int main(){
	int ans = DijkstraTest();
	cout << "ans: "  << ans << endl;
	
	return 0;
}
