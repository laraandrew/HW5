#include <iostream>
#include <sstream>
#include "Graph.h"

using namespace std;

// g++ -Wall BetterPriorityQueue.cpp -o bpq-tests
// ./bpq-tests

struct DNode {
    int pri = INT_MAX;
    bool visited = false;
    const GraphNode *node = nullptr;
    bool operator<(const DNode &other) const {
        return pri < other.pri;
    }
    bool operator>(const DNode &other) const {
        return pri > other.pri;
    }
    bool operator==(const DNode &other) const {
        return node == other.node;
    }
};

class BetterPriorityQueue{
    private: 
        vector<DNode> c;
    
    /**
     * This function is responsible for checking if the Dnode parameter is present within the queue
     */
    bool Contains(DNode n){
        if (c.size() == 0) return false;
            
        for (unsigned int i = 0; i < c.size(); i++){
            if (c.at(i).node == n.node) return true;
        }
        return false;
    }

    /**
     * This function is responsible for updating the queue with the given node
     * if the queue was updated, it will return true and false otherwise
     */
    bool Update(DNode n){
        bool updated = true;
        vector<DNode> updatedC;
        for (unsigned int i = 0; i < c.size(); i++){
            if (c.at(i) == n){
                if (c.at(i).pri <= n.pri){
                    updated = false;
                }
                else {
                    c.at(i).pri = n.pri;
                }
            }
        }
        updatedC = c;
        c.erase(c.begin(), c.end());
        
        for (unsigned int i = 0; i < updatedC.size(); i++){
            this->push(updatedC.at(i));
        }
        
        return updated;			
    }

    /**
     * function turns queue into string
     * @return string form of queue
     */
    string ToString(){
        stringstream bpqStr;

        for (unsigned int i = 0; i < c.size(); i++){
            if (i < c.size() - 1){
                bpqStr << DnodeToString(c.at(i)) << ", ";
            }
            else {
                bpqStr << DnodeToString(c.at(i)) << "]";
            }
        }
        
        return "[" + bpqStr.str() + "]";
    }

    /**
     * This function takes in a Dnode and returns it in a string form:
     * (key : pri)
     */
    string DnodeToString(DNode n){
        stringstream ss;
        ss << n.node->key;
        return "(" + ss.str() + " : " + to_string(n.pri) + ")";
    }

};

