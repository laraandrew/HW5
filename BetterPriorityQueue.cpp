#include <iostream>

using namespace std;

class BetterPriorityQueue{
    
    /**
     * function chekcs to see if node is in queue
     * @param n node being checked
     * @return true if it exists and flase if it doesnt
     */
    bool Contains(DNode n){
        bool containsNode = false;
            
        if (c.size() == 0){
            return false;
        }
            
        for (unsigned int i = 0; i < c.size(); i++){
            if (c.at(i).node == n.node){
                containsNode = true;
                break;
            }
        }
        
        return containsNode;
    }

    /**
     * function updates the priority value of give node
     * @param n node being updated
     * @return true if it was updated and false if it wasn't
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
        string bpqStr = "[";
        
        for (unsigned int i = 0; i < c.size(); i++){
            if (i < c.size()-1){
                bpqStr = bpqStr + DnodeToString(c.at(i)) + ", ";
            }
            else {
                bpqStr = bpqStr + DnodeToString(c.at(i)) + "]";
            }
        }
        
        return bpqStr;
    }

    /**
     * function turns node into string
     * @param node bing turned to string
     * @return string form of a node
     */
    string DnodeToString(DNode n){
        string dNodeStr = "(";
        
        dNodeStr = dNodeStr + n.node->key + ": " + to_string(n.pri) + ")";
        
        return dNodeStr;
    }

};

