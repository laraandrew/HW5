 #include <string>
 #include <vector>
 #include <iostream>

using namespace std;

struct GraphNode {
	char key;
	int data; // Not necessary or used for Dijkstra algorithm
};


struct GraphEdge {
	GraphNode *from;
	GraphNode *to;
	unsigned int weight;
};


class Graph{
	
	public:
		~Graph();
	
		GraphNode *AddNode(char key, int data = 0);
		GraphEdge *AddEdge(GraphNode *gn1, GraphNode *gn2, unsigned int weight = 0);
		
		string NodesToString() const;
		string ToString() const;

		static string GraphNodeToString(const GraphNode *gn);
		static string GraphEdgeToString(const GraphEdge *ge);
		
		// https://stackoverflow.com/questions/15106690/how-does-ampersand-in-the-return-type-of-a-function-declaration-work
		const vector<GraphEdge*>& GetEdges(const GraphNode *gn) const;
		const vector<GraphNode*>& GetNodes() const;

		const GraphNode* NodeAt(unsigned int idx) const;
		
		size_t Size() const; // the number of edges
		size_t Order() const; // the number of nodes

	private:
        vector<GraphNode*> vectNodes;
        vector<GraphEdge*> vectEdges;
		vector<vector<GraphEdge*> > vectAdj;


};
