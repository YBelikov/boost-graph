#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <list>
#include <vector>

#include <iostream>
#include<fstream>
#include <iterator>
#include <algorithm>
#include <vector>


using boost::adjacency_list;
using std::vector;

using graph = adjacency_list<>;
using size_type = boost::graph_traits<graph>::vertices_size_type;
using vertex_t = boost::graph_traits<graph>::vertex_descriptor;



template<typename Graph>
void printGraph(const Graph& g);


void topoSortDFS(const graph&, vertex_t, vertex_t*&, vector<int>&);
void topoSort(const graph&, vertex_t*);



int main()
{
	using graph = adjacency_list<>;
	using size_type = boost::graph_traits<graph>::vertices_size_type;
	size_type nVertices;
	std::ifstream fileIn("graph.txt");
	if (!fileIn) std::cout << "Error\n";
	fileIn >> nVertices;
	std::istream_iterator<std::pair<size_type, size_type>> inputBegin(fileIn), inputEnd;
 	graph g(inputBegin, inputEnd, nVertices);
	vector<std::string> fileNames(num_vertices(g));
	std::ifstream names("names.txt");
	if (!names) std::cout << "Error\n";
	typename boost::graph_traits<graph>::vertex_iterator it;
	typename boost::graph_traits<graph>::vertex_iterator itEnd;
	for (boost::tie(it, itEnd) = vertices(g); it != itEnd; ++it) {
		names >> fileNames[*it];
	}
	vector<vertex_t> order(num_vertices(g));
	topoSort(g, &order[0] + num_vertices(g));
	for (int i = 0; i < num_vertices(g); ++i) {
		std::cout << fileNames[order[i]] <<'\n';
	}
	return 0;
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

namespace std {
	template<typename T>
	std::istream& operator>>(std::istream& in, std::pair<T, T>& pair) {
		in >> pair.first >> pair.second;
		return in;
	}
}
