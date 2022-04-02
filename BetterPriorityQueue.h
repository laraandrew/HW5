 #ifndef BETTERPRIORITYQUEUE_H
 #include <string>
 #include <vector>
 #include <iostream>
 #include <queue>
 #include "DNode.cpp"


class BetterPriorityQueue : public priority_queue<DNode, vector<DNode>, greater<DNode> >::priority_queue{
    public:
        bool Contains(DNode n);
        bool Update(DNode n);
        string ToString();
        string DnodeToString(DNode n);

    private: 
        vector<DNode> c;
};

 #endif