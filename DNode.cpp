#ifndef DNODE_CPP
#include <iostream>

struct DNode {
    int pri = INT8_MAX;
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
#endif