#include "Graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stdio.h>

using namespace std;

/**
 * destructor clears up memory leaks
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
 * function adds node to the graph
 * @param key key of the node
 * @param data data of the node
 * @return node that was added to the graph
 */ 	
GraphNode *Graph::AddNode(char key, int data){
	GraphNode *vertex = new GraphNode;
	bool keyPresent = false;
	unsigned int idx = 0;
	
	vertex->key = key;
	vertex->data = data;
	
	if (vectNodes.size() > 0){
		if (vectNodes.size() == 1){
			if (vectNodes.at(0)->key == key){
				keyPresent = true;
			}
		}
		else {
			while (idx < vectNodes.size()){
				if (vectNodes.at(idx)->key == key){
					keyPresent = true;
					break;
				}
				idx += 1;
			}
		}
		if (!keyPresent){
			vectNodes.push_back(vertex);
		} 
		else {
			delete vertex;
			throw invalid_argument("key is already present");
		}
	}
	else {
		vectNodes.push_back(vertex);
	} 
	
	return vertex;
	delete vertex;
}

/**
 * function adds edge to the graph
 * @param gn1 node from
 * @param gn2 node to
 * @param weight weight of the edge
 * @return edge that was added to the graph
 */ 
GraphEdge *Graph::AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight){
	GraphEdge *edge = new GraphEdge;
	unsigned int idx = 0;
	int numNodePresent = 0;
	bool edgeExisting = false;
	
	edge->from = gn1;
	edge->to = gn2;
	edge->weight = weight;
	
	while (idx < vectNodes.size()){
		if (vectNodes.at(idx)->key == gn1->key || vectNodes.at(idx)->key == gn2->key){
			numNodePresent += 1;
		}
		if (numNodePresent == 2){
			break;
		}
		idx += 1;
	}
	
	idx = 0;
	
	if (vectEdges.size() > 1){
		while (idx < vectEdges.size()){
			if (vectEdges.at(idx)->from == gn1 && vectEdges.at(idx)->to == gn2){
				edgeExisting = true;
				break;
			}
			idx += 1;
		}
	}

	if (vectEdges.size() == 1){
		if (vectEdges.at(0)->from == gn1 && vectEdges.at(0)->to == gn2){
			edgeExisting = true;
		}
	}
	
	if (numNodePresent == 2 && !edgeExisting){	
		vectEdges.push_back(edge);
		if (vectAdj.size() == 0){
			vector<GraphEdge*> edgeVec;
			vectEdges.push_back(edge);
			vectAdj.push_back(edgeVec);
		}
		else {
			for (unsigned int i = 0; i < vectAdj.size(); i++){
				cout << "in the forloop" << endl;
				if (vectAdj.at(i).at(0)->from == gn1){
					edgeExisting = true;
					idx = i;
					break;
				}
			}
			if (edgeExisting){
				vectAdj.at(idx).push_back(edge);
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
		throw invalid_argument("either edge already exists or one or both nodes don't exist");
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
 * function that turns graph into string
 * @return string form of graph
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
	const vector<GraphEdge*> &emptyVec = {};
	
	for (unsigned int i = 0; i < vectAdj.size(); i++){
		if (vectAdj.at(i).at(0)->from->key == graphN->key){
			return vectAdj.at(i);
		}
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
	 

