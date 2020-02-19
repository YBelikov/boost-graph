#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <list>
#include <vector>

#include <iostream>
#include<fstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>

#include "./headers/DFSVisitor.h"

namespace boost {
	enum vertex_compile_cost_t { vertex_compile_cost = 111 };
	BOOST_INSTALL_PROPERTY(vertex, compile_cost);
}

using boost::adjacency_list;
using std::vector;
using boost::default_color_type;



using graph = adjacency_list < boost::listS, boost::listS, boost::directedS,
	boost::property<boost::vertex_name_t, std::string, boost::property<boost::vertex_distance_t, float, boost::property<boost::vertex_color_t, default_color_type,
	boost::property<boost::vertex_compile_cost_t, float>>>>, boost::property<boost::edge_weight_t, float>>;

using vertex_t = typename boost::graph_traits<graph>::vertex_descriptor;
using name_map_t = typename boost::property_map<graph, boost::vertex_name_t>::type;
using compile_cost_map_t = typename boost::property_map<graph, boost::vertex_compile_cost_t>::type;
using distance_map_t = typename boost::property_map<graph, boost::vertex_distance_t>::type;
using color_map_t = typename boost::property_map< graph, boost::vertex_color_t>::type;
using size_type = boost::graph_traits<graph>::vertices_size_type;



template<typename Graph>
void printGraph(const Graph& g);

template<typename Graph>
Graph fillGraph(const std::string&);

vector<std::string> getFileNames(const graph&);


template<typename Graph, typename OutputIterator, typename ColorMap>
void topoSort(const Graph&, OutputIterator, ColorMap);

template<typename Graph, typename Visitor, typename ColorMap>
void genericDFS(const Graph&, Visitor, ColorMap);

template<typename Graph, typename Visitor, typename ColorMap>
void dfs(const Graph&, typename boost::graph_traits<Graph>::vertex_descriptor, Visitor, ColorMap);


template<typename Graph>
Graph fillGraph(const std::string& graphFile) {
	size_type nVertices;
	std::ifstream fileIn(graphFile.c_str());
	if (!fileIn) std::cout << "Error\n";
	fileIn >> nVertices;
	std::istream_iterator<std::pair<size_type, size_type>> inputBegin(fileIn), inputEnd;
	Graph g(inputBegin, inputEnd, nVertices);
	return g;
}

template<typename Graph>
void printGraph(const Graph& g) {
	typename boost::graph_traits<Graph>::edge_iterator edgesBegin, edgesEnd;
	for (tie(edgesBegin, edgesEnd) = edges(g); edgesBegin != edgesEnd; ++edgesBegin) {
		std::cout << *edgesBegin << '\n';
	}
}

template<typename Graph, typename OutputIterator, typename ColorMap>
void topoSort(const Graph& g, OutputIterator topoOrder, ColorMap color) {
	DFSVisitor<OutputIterator> topoVisitor(topoOrder);
	genericDFS(g, topoVisitor, color);
}

template<typename Graph, typename Visitor, typename ColorMap>
void genericDFS(const Graph& g, Visitor vis, ColorMap color) {
	using Color = boost::color_traits<typename boost::property_traits<ColorMap>::value_type>;
	typename boost::graph_traits<Graph>::vertex_descriptor vBegin, vEnd;
	for (tie(vBegin, vEnd) = vertices(g); vBegin != vEnd; ++vBegin) {
		color[*vBegin] = Color::white();
		for (tie(vBegin, vEnd) = vertices(g); vBegin != vEnd; ++vBegin) {
			if (color[*vBegin] == Color::white()) {
				dfs(g, *vBegin, vis, color);
			}
		}
	}
}


template<typename Graph, typename Visitor, typename ColorMap>
void dfs(const Graph& g, typename boost::graph_traits<Graph>::vertex_descriptor vertex, Visitor vis, ColorMap color) {
	using colorType = typename boost::property_traits<ColorMap>::value_type;
	using colorTraits = typename boost::color_traits<colorType>::value_type;
	color[vertex] = colorTraits::gray();
	vis.discoverVertex(vertex, g);
	typename graph_traits<Graph>::edge_iterator eBegin, eEnd;
	if (color[*eBegin] == colorTraits::white()) {
		vis.treeEdge(*eBegin, g);
		dfs(g, boost::target(*eBegin, g), vis, color);
	}
	else if (color[*eBegin] == colorTraits::gray()) {
		vis.backEdge(*eBegin, g);
		dfs(g, boost::target(*eBegin, g), vis, color);
	}
	else {
		vis.towardOrCrossEdge(*eBegin, g);
	}
	color[vertex] = colorTraits::black();
	vis.finishVertex(vertex, g);
}

namespace std {
	template<typename T>
	std::istream& operator>>(std::istream& in, std::pair<T, T>& pair) {
		in >> pair.first >> pair.second;
		return in;
	}
}
