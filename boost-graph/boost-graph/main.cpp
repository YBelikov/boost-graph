#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <list>
#include <vector>

#include <iostream>
#include <iterator>
#include <algorithm>

using boost::adjacency_list;

template<typename Graph>
void printGraph(const Graph& g);

int main()
{
	using graph = adjacency_list<>;
	using size_type = boost::graph_traits<graph>::vertices_size_type;
	size_type nVertices;
	std::cin >> nVertices;
	std::istream_iterator<std::pair<size_type, size_type>> inputBegin(std::cin), inputEnd;
	graph g(inputBegin, inputEnd, nVertices);
	printGraph<graph>(g);
	return 0;
}

template<typename Graph>
void printGraph(const Graph& g) {
	typename boost::graph_traits<Graph>::edge_iterator edgesBegin, edgesEnd;
	for (tie(edgesBegin, edgesEnd) = edges(g); edgesBegin != edgesEnd; ++edgesBegin) {
		std::cout << *edgesBegin << '\n';
	}
}


namespace std {
	template<typename T>
	std::istream& operator>>(std::istream& in, std::pair<T, T>& pair) {
		in >> pair.first >> pair.second;
		return in;
	}
}
