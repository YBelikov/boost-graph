
#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/lexical_cast.hpp>
#include "CyclesRecording.h"
#include <vector>
#include <iostream>

using boost::adjacency_list;
using boost::graph_traits;
using std::vector;
using std::cout;
using boost::add_edge;

int main(){	
	using Graph = adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS>;
	using Vertex = typename graph_traits<Graph>::vertex_descriptor;
	int numberOfEdges{ 5 };
	Graph graph(numberOfEdges);
	add_edge(0, 1, graph);
	add_edge(1, 2, graph);
	add_edge(2, 3, graph);
	add_edge(3, 4, graph);
	add_edge(4, 1, graph);
	auto vertices = boost::vertices(graph);
	Vertex entry = *(vertices.first);
	vector<Vertex> loops;
	cyclesRecording(graph, entry, loops);
	cout << "Next vertices belongs to loops in graph: \n";
	for (auto& vertex : loops) {
		cout << vertex << '\n';
	}
	return 0;
}