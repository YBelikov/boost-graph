#pragma once
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <vector>
#include "BackEdgeRecorder.h"

using boost::graph_traits;
using boost::default_color_type;
using boost::function_requires;
using std::vector;

template<typename Graph, typename Loops>
void computeLoopExtent(typename graph_traits<Graph>::edge_descriptor backEdge, const Graph& graph, Loops& loops);

template<typename Graph, typename Loops>
void cyclesRecording(const Graph& graph, typename graph_traits<Graph>::vertex_descriptor entryVertex, Loops& loops) {
	function_requires<boost::BidirectionalGraphConcept<Graph>>();
	using Edge = typename graph_traits<Graph>::edge_descriptor;
	using Vertex = typename graph_traits<Graph>::vertex_descriptor;
	vector<default_color_type> vertexColors(boost::num_vertices(graph));
	vector<Edge> backEdges;
	boost::depth_first_visit(graph, entryVertex, makeBackEdgeRecorder(std::back_inserter(backEdges)),
		boost::make_iterator_property_map(vertexColors.begin(), boost::get(boost::vertex_index, graph)));
	for (auto& edge : backEdges) {
		loops.push_back(typename Loops::value_type());
		computeLoopExtent(edge, graph, loops);
	}
	
}

template<typename Graph, typename Loops>
void computeLoopExtent(typename graph_traits<Graph>::edge_descriptor backEdge, const Graph& graph, Loops& loops) {
	function_requires<boost::BidirectionalGraphConcept<Graph>>();
	using Vertex = typename graph_traits<Graph>::vertex_descriptor;
	using Color = typename boost::color_traits<default_color_type>;
	Vertex loopHead, loopTail;
	loopHead = boost::source(backEdge, graph);
	loopTail = boost::target(backEdge, graph);
	vector<default_color_type>reachableFromHead(boost::num_vertices(graph));
	boost::depth_first_visit(graph, loopHead, default_dfs_visitor(), boost::make_iterator_property_map(reachableFromHead.begin(), boost::get(boost::vertex_index, graph)));
	boost::reverse_graph<Graph> rGraph(graph);
	vector<default_color_type> reachableToTail(boost::num_vertices(rGraph));
	boost::depth_first_visit(rGraph, loopTail, default_dfs_visitor(), boost::make_iterator_property_map(reachableToTail.begin(), boost::get(boost::vertex_index, graph)));
	auto vertices = boost::vertices(graph);
	for (auto verticesIterator = vertices.first; verticesIterator != vertices.second; ++verticesIterator) {
		if (reachableFromHead[*verticesIterator] != Color::white() && reachableToTail[*verticesIterator] != Color::white()) {
			loops.push_back(*verticesIterator);
		}
	}
}
