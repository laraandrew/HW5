#include <functional>
#include <queue>
#include <vector>
#include <iostream>

class BetterPriorityQueue: public priority_queue<DNode, vector<DNode>, 
greater<DNode>>::priority_queue { 
// ... your code goes here ...
};