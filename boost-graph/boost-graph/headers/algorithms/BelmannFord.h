#pragma once
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <algorithm>
using std::pair;

template<typename Graph, typename WeightMap, typename DistanceMap, typename PredeccessorsMap>
void edgeRelaxation(const Graph& graph, WeightMap weights, DistanceMap distances, PredeccessorsMap parents);

template<typename Graph, typename WeightMap, typename DistanceMap, typename PredeccessorsMap>
bool belmannFord(const Graph& graph, int numberOfVertices, WeightMap weights, DistanceMap distances, PredeccessorsMap parents);


template<typename Graph, typename WeightMap, typename DistanceMap, typename PredeccessorsMap>
bool belmannFord(const Graph& graph, int numberOfVertices, WeightMap weights, DistanceMap distances, PredeccessorsMap parents) {

	typename boost::graph_traits<Graph>::edge_iterator edgeBegin, edgeEnd;
	for (int i{}; i < numberOfVertices - 1; ++i) {
		edgeRelaxation(graph, weights, distances, parents);
	}
	for (boost::tie(edgeBegin, edgeEnd) = boost::edges(graph); edgeBegin != edgeEnd; ++edgeBegin) {
		vertex_t sourceVertex = boost::source(*edgeBegin, graph);
		vertex_t targetVertex = boost::target(*edgeBegin, graph);
		if (distances[sourceVertex] + weights[*edgeBegin] < distances[targetVertex]) {
			return false;
		}
	}
	return true;
}


template<typename Graph, typename WeightMap, typename DistanceMap, typename PredeccessorsMap>
void edgeRelaxation(const Graph& graph, WeightMap weights, DistanceMap distances, PredeccessorsMap parents) {
	typename boost::graph_traits<Graph>::edge_iterator edgeBegin, edgeEnd;
	for (boost::tie(edgeBegin, edgeEnd) = boost::edges(graph); edgeBegin != edgeEnd; ++edgeBegin) {
		vertex_t sourceVertex = boost::source(*edgeBegin, graph);
		vertex_t targetVertex = boost::target(*edgeBegin, graph);
		if (distances[sourceVertex] + weights[*edgeBegin] < distances[targetVertex]) {
			distances[targetVertex] = distances[sourceVertex] + weights[*edgeBegin];
			parents[targetVertex] = sourceVertex;
		}
	}
}