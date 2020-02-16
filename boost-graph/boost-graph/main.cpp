#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <list>
#include <vector>

#include <iostream>
#include<fstream>
#include <iterator>
#include <algorithm>
#include <vector>


using boost::adjacency_list;
using std::vector;
using boost::default_color_type;

using graph = adjacency_list<>;
using size_type = boost::graph_traits<graph>::vertices_size_type;
using vertex_t = boost::graph_traits<graph>::vertex_descriptor;
using graph = adjacency_list<>;
using size_type = boost::graph_traits<graph>::vertices_size_type;



template<typename Graph>
void printGraph(const Graph& g);

template<typename Graph>
Graph fillGraph();

vector<std::string> getFileNames(const graph&);

void topoSortDFS(const graph&, vertex_t, vertex_t*&, vector<int>&);
void topoSort(const graph&, vertex_t*);

bool hasCycle(const graph&);
bool hasCycleDFS(const graph&, vertex_t, default_color_type*);

int main()
{
	graph g = fillGraph<graph>();
	vector<std::string> fileNames = getFileNames(g);
	
	vector<vertex_t> order(num_vertices(g));
	
	if (hasCycle(g)) {
		std::cout << "Cycle detected!\n";
		return -1;
	}


	topoSort(g, &order[0] + num_vertices(g));
	for (int i = 0; i < num_vertices(g); ++i) {
		std::cout << fileNames[order[i]] <<'\n';
	}
	return 0;
}

template<typename Graph>
Graph fillGraph() {
	size_type nVertices;
	std::ifstream fileIn("graph.txt");
	if (!fileIn) std::cout << "Error\n";
	fileIn >> nVertices;
	std::istream_iterator<std::pair<size_type, size_type>> inputBegin(fileIn), inputEnd;
	Graph g(inputBegin, inputEnd, nVertices);
	return g;
}

vector<std::string> getFileNames(const graph& g) {
	vector<std::string> fileNames{num_vertices(g)};
	std::ifstream names("names.txt");
	if (!names) std::cout << "Error\n";
	typename boost::graph_traits<graph>::vertex_iterator it;
	typename boost::graph_traits<graph>::vertex_iterator itEnd;
	for (boost::tie(it, itEnd) = vertices(g); it != itEnd; ++it) {
		names >> fileNames[*it];
	}
	return fileNames;
}

template<typename Graph>
void printGraph(const Graph& g) {
	typename boost::graph_traits<Graph>::edge_iterator edgesBegin, edgesEnd;
	for (tie(edgesBegin, edgesEnd) = edges(g); edgesBegin != edgesEnd; ++edgesBegin) {
		std::cout << *edgesBegin << '\n';
	}
}

void topoSort(const graph& g, vertex_t* topoOrder) {
	vector<int> mark( num_vertices(g), 0 );
	typename boost::graph_traits<graph>::vertex_iterator vi;
	typename boost::graph_traits<graph>::vertex_iterator viEnd;
	for (boost::tie(vi, viEnd) = vertices(g); vi != viEnd; ++vi) {
		if (mark[*vi] == 0) {
			topoSortDFS(g, *vi, topoOrder, mark);
		}
	}

}


void topoSortDFS(const graph& g, vertex_t u, vertex_t*& topoOrder, vector<int>& mark) {
	mark[u] = 1;
	typename boost::graph_traits<graph>::adjacency_iterator it;
	typename boost::graph_traits<graph>::adjacency_iterator itEnd;
	for (tie(it, itEnd) = adjacent_vertices(u, g); it != itEnd; ++it) {
		if (mark[*it] == 0) topoSortDFS(g, *it, topoOrder, mark);
	}
	*--topoOrder = u;
}

bool hasCycle(const graph& g) {
	vector<default_color_type> colors(num_vertices(g), boost::white_color);
	typename boost::graph_traits<graph>::vertex_iterator vBeg, vEnd;
	for (boost::tie(vBeg, vEnd) = vertices(g); vBeg != vEnd; ++vBeg) {
		if (colors[*vBeg] == boost::white_color) {
			if (hasCycleDFS(g, *vBeg, &colors[0])) return true;
		}
	}
	return false;
}

bool hasCycleDFS(const graph& g, vertex_t vertex, default_color_type* colors) {
	colors[vertex] = boost::gray_color;
	typename boost::graph_traits<graph>::adjacency_iterator vBeg, vEnd;
	for (tie(vBeg, vEnd) = adjacent_vertices(vertex, g); vBeg != vEnd; ++vBeg) {
		if (colors[*vBeg] == boost::white_color) {
			if (hasCycleDFS(g, *vBeg, colors)) {
				return true;
			}
		}
		else if (colors[*vBeg] == boost::gray_color) return true;
	}
	colors[vertex] = boost::black_color;
	return false;
}

namespace std {
	template<typename T>
	std::istream& operator>>(std::istream& in, std::pair<T, T>& pair) {
		in >> pair.first >> pair.second;
		return in;
	}
}
