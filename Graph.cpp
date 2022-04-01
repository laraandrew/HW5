#include "Graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stdio.h>

using namespace std;

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
	
	
	if (vectNodes.size() > 0){
		if (vectNodes.size() == 1 && vectNodes.at(0)->key == key) keyInUse = true; // if the key is found in the 
		else {
			while (index < vectNodes.size()){ // iterate through the node Vector to see if the key is already in use
				if (vectNodes.at(index)->key == key){
					keyInUse = true;
					break;
				}
				index++;
			}
		}
		if (!keyInUse) vectNodes.push_back(node);
		else {
			delete node;
			throw invalid_argument("Key is in use");
		}
	}
	else vectNodes.push_back(node); //pushes node into the node vector if its an empty vector
	
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
	int numNodePresent = 0;
	bool edgeFound = false;
	
	
	while (index < vectNodes.size()){
		if (vectNodes.at(index)->key == FromNode->key || vectNodes.at(index)->key == ToNode->key) numNodePresent++; 
		if (numNodePresent == 2) break; // break once both nodes are found as expressed above
		index++;
	}
	index = 0;
	
	if (vectEdges.size() > 1){ // make sure the size of the vector is greater than one
		while (index < vectEdges.size()){
			if (vectEdges.at(index)->from == FromNode && vectEdges.at(index)->to == ToNode){
				edgeFound = true;
				break;
			}
			index++;
		}
	}

	if (vectEdges.size() == 1){
		if (vectEdges.at(0)->from == FromNode && vectEdges.at(0)->to == ToNode) edgeFound = true; // the edge has been found in the vector of edges
	}
	
	if (numNodePresent == 2 && !edgeFound){	//if both the from and to Nodes are found and the edge does not exist yet
		vectEdges.push_back(edge);
		if (vectAdj.size() == 0){
			vector<GraphEdge*> edgeVec;
			vectEdges.push_back(edge);
			vectAdj.push_back(edgeVec);
		}
		else {
			for (unsigned int i = 0; i < vectAdj.size(); i++){
				cout << "in the forloop" << endl;
				if (vectAdj.at(i).at(0)->from == FromNode){
					edgeFound = true;
					index = i;
					break;
				}
			}
			if (edgeFound){
				vectAdj.at(index).push_back(edge);
			}
			else {
				vector<GraphEdge*> edgeVec;
				edgeVec.push_back(edge);
				vectAdj.push_back(edgeVec);
			}
		}
		return edge;
		delete edge;
	} 
	else {
		delete edge;
		if(edgeFound) throw invalid_argument("edge already exists in the Edge Vector");
		if (numNodePresent < 2) throw invalid_argument("one or both nodes don't exist");
	}
}

/**
 * function that turns nodes in graph to string
 * @return string form of nodes
 */ 	
string Graph::NodesToString() const{
	string nodeStr = "[";
	bool first = true;
	GraphNode* node;
	for (unsigned int i = 0; i < vectNodes.size(); i++){
		if (first){
			nodeStr = nodeStr + "(" + node->key + ":" + to_string(node->data) + ")";
			first = false;
		}
		else { 
			nodeStr = nodeStr + ", " + "(" + node->key + ":" + to_string(node->data) + ")";
		}
	}
	
	nodeStr = nodeStr + "]";
	
	return nodeStr;
}

/**
 * This function turns the graph into a string completely with new lines betwee
 */ 
string Graph::ToString() const{
	stringstream adjListStr;
	
	for (unsigned int p = 0; p < vectNodes.size(); p++){
		adjListStr << vectNodes.at(p)->key << " | ";
		for (unsigned int r = 0; r < vectAdj.size(); r++){
			if (vectNodes.at(p)->key == vectAdj.at(r).at(0)->from->key){
				if (vectAdj.at(r).size() > 0){
					for (unsigned int q = 0; q < vectAdj.at(r).size(); q++){
						if (q == vectAdj.at(r).size() - 1){
						adjListStr << "[(" << (vectAdj.at(r).at(q)->from->key) << ":" << to_string(vectAdj.at(r).at(q)->from->data) << ")->(" << vectAdj.at(r).at(q)->to->key << ":" << to_string(vectAdj.at(r).at(q)->to->data) << ") w:" << to_string(vectAdj.at(r).at(q)->weight) << "]";
						}
						else {						
							adjListStr << "[(" << (vectAdj.at(r).at(q)->from->key) << ":" << to_string(vectAdj.at(r).at(q)->from->data) << ")->(" << vectAdj.at(r).at(q)->to->key << ":" << to_string(vectAdj.at(r).at(q)->to->data) << ") w:" << to_string(vectAdj.at(r).at(q)->weight) << "], ";
						}
					}
				}
			}
		}
		adjListStr << "\n"; // add a new line at the end of each iteration
	}
	return adjListStr.str();
}

/**
 * function turns node into string given node
 * @param gn node being turned to string
 * @return string form of node
 */ 
string Graph::GraphNodeToString(const GraphNode *GraphN){
	stringstream sstream;
	sstream << GraphN->key;

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
	const vector<GraphEdge*> emptyVec; // gonna need to add & sign to make it reference vector
	
	for (unsigned int i = 0; i < vectAdj.size(); i++){
		if (vectAdj.at(i).at(0)->from->key == graphN->key) return vectAdj.at(i);
	}
	return emptyVec;
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
	 

