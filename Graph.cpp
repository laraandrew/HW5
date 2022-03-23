#include <functional>
#include <queue>
#include <vector>
#include <iostream>

#include "TemplateGraph.h"


 GraphNode *AddNode(char key, int data = 0){

}
GraphEdge *AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight = 0){

}
		
string Graph:: NodesToString() const{

}
string Graph:: ToString() const{

}

static string GraphNodeToString(const GraphNode *gn){

}
static string GraphEdgeToString(const GraphEdge *ge){

}
		
	// https://stackoverflow.com/questions/15106690/how-does-ampersand-in-the-return-type-of-a-function-declaration-work
const vector<GraphEdge*>& GetEdges(const GraphNode *gn) const{

}
const vector<GraphNode*>& GetNodes() const{

}

const GraphNode* NodeAt(unsigned int idx) const{

}
		
size_t Graph::Size() const{ // the number of edges

}
size_t Graph::Order() const{// the number of nodes
}


int main() {
    return 0;
}