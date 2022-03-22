#include <functional>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class BetterPriorityQueue: public priority_queue<DNode, vector<DNode>, 
greater<DNode>>::priority_queue { 
// ... your code goes here ...
};