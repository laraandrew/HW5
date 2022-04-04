#include "Graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stdio.h>

using namespace std;

//g++ -Wall Graph.cpp -o graph-tests
//./graph-tests

/**
 * Deconstructor function responsible for memory leaks when exiting the program
 */
Graph::~Graph(){
	for (unsigned int i = 0; i < vectNodes.size(); i++){
		delete &vectNodes.at(i);
		vectNodes.erase(vectNodes.begin() + i);
	}
	for (unsigned int i = 0; i < vectEdges.size(); i++){
		delete &vectEdges.at(i);
		vectEdges.erase(vectEdges.begin() + i);
	}
}

/**
 * This function creates a new node using the parameters of: key and data 
 * Adds this new node to the vector of nodes
 */ 	
GraphNode *Graph::AddNode(char key, int data){
	GraphNode *node = new GraphNode;
	node->key = key;
	node->data = data;

	bool keyInUse = false;
	unsigned int index = 0;
	if (vectNodes.size() == 0) vectNodes.push_back(node);
	
	while (index < vectNodes.size()){ // iterate through the node Vector to see if the key is already in use
		if (vectNodes.at(index)->key == key){
			keyInUse = true;
			break;
		}
		index++;
	}
	if (!keyInUse) vectNodes.push_back(node);
	else{
		delete node;
		throw invalid_argument("Key is in use");
	}
	return node;
	delete node;
}

/**
 * This function takes in a "FromNode", "ToNode" and the weight of the edge
 */ 
GraphEdge *Graph::AddEdge(GraphNode *FromNode, GraphNode *ToNode, unsigned int weight){
	GraphEdge *edge = new GraphEdge;
	edge->from = FromNode;
	edge->to = ToNode;
	edge->weight = weight;
	//edge is now declared and initialized

	unsigned int index = 0;
	bool edgeFound = false;
	int numNodePresent = 0;
	
	while (index < vectNodes.size()){ //this runs through the vector of nodes to find the desired nodes (make sure they exist)
		if (vectNodes.at(index)->key == FromNode->key || vectNodes.at(index)->key == ToNode->key) numNodePresent++;
		if (numNodePresent == 2) break; // break once both nodes are found as expressed above
		index++;
	}
	index = 0;
	
	if (vectEdges.size() >= 1){ // make sure the size of the vector is greater than one
		while (index < vectEdges.size()){
			if (vectEdges.at(index)->from == FromNode && vectEdges.at(index)->to == ToNode){ // running through vector to see if this edge already exists
				edgeFound = true;
				break;
			}
			index++;
		}
	}

	if (numNodePresent == 2 && !edgeFound){	//if both the from and to Nodes are found and the edge does not exist yet
		vectEdges.push_back(edge);
		if (vectAdj.size() == 0){
			vector<GraphEdge*> edgeVec;
			edgeVec.push_back(edge);
			vectAdj.push_back(edgeVec);
		}
		else {
			for (unsigned int i = 0; i < vectAdj.size(); i++){
				if (vectAdj.at(i).at(0)->from == FromNode){
					vectAdj.at(index).push_back(edge);
					index = i;
					break;
				}
			}
			vector<GraphEdge*> edgeVec;
			edgeVec.push_back(edge);
			vectAdj.push_back(edgeVec);
		}
		return edge;
		delete edge;
	} 
	else {
		delete edge;
		if(edgeFound) throw invalid_argument("edge already exists in the Edge Vector");
		if (numNodePresent < 2) throw invalid_argument("one or both nodes don't exist");
	}
	return edge;
}

/**
 * This function is responsible for turning the Vector of Nodes into a string
 * expresses as such: [(key:data), (key:data) ...]
 */ 	
string Graph::NodesToString() const{
	stringstream nodeStream;
	nodeStream << "[";
	GraphNode* node = vectNodes.at(0);
	nodeStream << "(" << node->key << ":" << to_string(node->data) << ")";
	for (unsigned int i = 1; i < vectNodes.size(); i++){
		node = vectNodes.at(i);
		nodeStream << ", (" << node->key << ":" << to_string(node->data) << ")";
	}
	return nodeStream.str() + "]";
}

/**
 * This function turns the graph into a string completely with new lines 
 */ 
string Graph::ToString() const{
	stringstream adjVectStr;
	
	for (unsigned int p = 0; p < vectNodes.size(); p++){
		adjVectStr << vectNodes.at(p)->key << " | ";
		for (unsigned int r = 0; r < vectAdj.size(); r++){
			if (vectNodes.at(p)->key == vectAdj.at(r).at(0)->from->key){
				if (vectAdj.at(r).size() > 0){
					for (unsigned int q = 0; q < vectAdj.at(r).size(); q++){
						if (q == vectAdj.at(r).size() - 1){
							adjVectStr << "[(" << (vectAdj.at(r).at(q)->from->key) << ":" << to_string(vectAdj.at(r).at(q)->from->data) << ")->(" << vectAdj.at(r).at(q)->to->key << ":" << to_string(vectAdj.at(r).at(q)->to->data) << ") w:" << to_string(vectAdj.at(r).at(q)->weight) << "]";
						}
						else {
							adjVectStr << "[(" << (vectAdj.at(r).at(q)->from->key) << ":" << to_string(vectAdj.at(r).at(q)->from->data) << ")->(" << vectAdj.at(r).at(q)->to->key << ":" << to_string(vectAdj.at(r).at(q)->to->data) << ") w:" << to_string(vectAdj.at(r).at(q)->weight) << "], ";}
					}
				}
			}
		}
		adjVectStr << "\n"; // add a new line at the end of each iteration
	}
	return adjVectStr.str();
}

/**
 * This function is responsible for taking in a node and returning the key and data values of that node as such:
 * (key:data)
 */ 
string Graph::GraphNodeToString(const GraphNode *GraphN){
	stringstream sstream;
	sstream << GraphN->key; // turning char into string

	return "(" + sstream.str() + ":" + to_string(GraphN->data) + ")";
}

/**
 * This function takes in a graphEdge and turns its nodes into a string
 */ 
string Graph::GraphEdgeToString(const GraphEdge *GraphN){
	stringstream stream;
	stream << GraphN->from->key;
	string keyFrom = stream.str();
	stream.clear();
	stream << GraphN->to->key; // will be used in return call
	
	return "[(" + keyFrom + ":" + to_string(GraphN->from->data) + ")" + "->(" + stream.str() + ":" + to_string(GraphN->to->data) + ") w:" + to_string(GraphN->weight) + "]";
}

/**
 * THis function uses the size of the vector of Adj to find and return the vector node
 */
const vector<GraphEdge*> &Graph::GetEdges(const GraphNode *graphN) const{
	const vector<GraphEdge*> emptyVec;
	for (unsigned int i = 0; i < vectAdj.size(); i++){
		if (vectAdj.at(i).at(0)->from->key == graphN->key) return vectAdj.at(i);
	}
	return emptyVec;// fix needed on line 197
}

/**
 * This function returns back the vector of nodes
 */
const vector<GraphNode*>& Graph::GetNodes() const{
	return vectNodes;
}

/**
 * This function returns the node at a given index
 */
const GraphNode* Graph::NodeAt(unsigned int idx) const{
	return vectNodes.at(idx);		
}

/**
 * This function counts all of the edges present and returns them
 */
size_t Graph::Size() const{
	size_t count = 0;
	for (unsigned int i = 0; i < vectAdj.size(); i++){
		for (unsigned int p = 0; p < vectAdj.at(i).size(); p++){
			count++;
		}
	}
	return count;
}

/**
 * This function returns the total amount of nodes in the vector
 */
size_t Graph::Order() const{
	
	return vectNodes.size(); // num of nodes
}
	 

