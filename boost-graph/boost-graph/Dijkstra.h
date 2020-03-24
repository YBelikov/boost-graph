#pragma once
#include <queue>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>


using std::priority_queue;
using std::vector;

template<typename Graph, typename VertexDescriptor, typename WeightMap, typename PredeccessorMap, typename DistanceMap>
bool dijkstraShortestPath(const Graph& graph, VertexDescriptor startingVertex, WeightMap weights, PredeccessorMap parents, DistanceMap distances) {
	
	enum Color {White, Gray, Black};
 	vector<Color> colors{ boost::num_vertices(graph) };
	using Pair = std::pair<int, VertexDescriptor>;
	auto vertices = boost::vertices(graph);
	for (auto vertexIterator = vertices.first; vertexIterator != vertices.second; ++vertexIterator) {
		colors[*vertexIterator] = Color::White;
	}
	priority_queue<Pair, vector<Pair>, std::greater<Pair>> vertexQueue{};
	vertexQueue.push(std::make_pair(distances[startingVertex], startingVertex));
	while (!vertexQueue.empty()) {
		Pair pair = vertexQueue.top();
		VertexDescriptor sourceVertex = pair.second;
		vertexQueue.pop();
		auto outEdges = boost::out_edges(sourceVertex, graph);
		for (auto outEdgesIterator = outEdges.first; outEdgesIterator != outEdges.second; ++outEdgesIterator) {
			auto targetVertex = boost::target(*outEdgesIterator, graph);
			if (distances[targetVertex] > distances[sourceVertex] + weights[boost::get(boost::edge_index, graph, *outEdgesIterator)]) {
				distances[targetVertex] = distances[sourceVertex] + weights[boost::get(boost::edge_index, graph, *outEdgesIterator)];
				parents[targetVertex] = sourceVertex;
				if (colors[targetVertex] = Color::White) {
					colors[targetVertex] = Color::Gray;
					vertexQueue.push(std::make_pair(distances[targetVertex], targetVertex));
				}
				else if (colors[targetVertex] == Color::Gray) {
					vertexQueue.push(std::make_pair(distances[targetVertex], targetVertex));
				}
				else {
					return false;
				}
			}
		}
		colors[sourceVertex] = Color::Black;
	}
	return true;
}

