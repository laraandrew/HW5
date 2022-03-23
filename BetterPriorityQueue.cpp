#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <climits>
#include "TemplateGraph.h"

using namespace std;

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

class BetterPriorityQueue: public priority_queue<DNode, vector<DNode>, greater<DNode>>::priority_queue { 
};