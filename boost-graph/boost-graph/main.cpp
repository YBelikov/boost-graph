#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "./headers/algorithms/TopoSort.h"
#include "./headers/algorithms/CycleDetection.h"
#include <boost/graph/edge_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <array>
#include <algorithm>
#include "./headers/algorithms/BelmannFord.h"

enum {A, B, C, D, E, F, G, H};
using std::array;
using std::pair;
using Edge = pair<int, int>; 
const int numberOfEdges = 11;
const int numberOfVertices = 8;

int main()
{
	array<Edge, numberOfEdges> edges = { Edge(A, B), Edge(A, C), Edge(B, D), Edge(B, E), Edge(C, F),
		Edge(C, E), Edge(D, H), Edge(D, E), Edge(E, H), Edge(F, G), Edge(G, H) };
	using Graph = boost::edge_list<array<Edge, numberOfEdges>::iterator>;
	Graph graph(edges.begin(), edges.end());


	array<float, numberOfEdges> weights = { 5.0, 1.0, 1.3, 3.0, 2.0, 10.0, 6.3, 0.4, 1.3, 1.2, 0.5 };
	auto weightMap = boost::make_iterator_property_map(weights.begin(), get(boost::edge_index, graph), weights[0]);
	array<float, numberOfVertices> distances;
	distances.assign(std::numeric_limits<float>::max());
	char names[] = "ABCDEFGH";
	distances[A] = 0;
	array<int, numberOfVertices> parents;
	for (int i{}; i < numberOfVertices; ++i) {
		parents[i] = i;
	}
	bool result = belmannFord(graph, numberOfVertices, &weights[0], &distances[0], &parents[0]);
	if (result) {
		for (int i = 0; i < numberOfVertices; ++i) {
			std::cout << names[i] << ' ' << distances[i] << ' ' << names[parents[i]] << '\n';
		}
	}
	else {
		std::cout << "Negative cicle detected\n";
	}
	/*std::string graphFile{ "./resources/graph.txt" };
	std::string graphWithCycleFile{ "./resources/graphWithCycle.txt" };
	std::string namesFile{ "./resources/names.txt" };
	std::string costsFile{ "./resources/costs.txt" };

	graph g = fillGraph<graph>(graphFile);
	std::ifstream namesStream{ namesFile.c_str() };
	std::vector<std::string> names(boost::num_vertices(g));
	typename boost::graph_traits<graph>::vertex_iterator vBegin1, vEnd1;
	for (int i= 0; i < boost::num_vertices(g); ++i) {
		namesStream >> names[i];
	}
	
	name_map_t name_map = get(boost::vertex_name, g);
	compile_cost_map_t compile_cost_map = get(boost::vertex_compile_cost, g);
	distance_map_t distance_map = get(boost::vertex_distance, g);
	color_map_t color_map = get(boost::vertex_color, g);

	std::ifstream verticesNames(namesFile.c_str());
	std::ifstream compileCosts(costsFile.c_str());

	typename boost::graph_traits<graph>::vertex_iterator vBegin, vEnd;
	for (boost::tie(vBegin, vEnd) = vertices(g); vBegin != vEnd; ++vBegin) {
		verticesNames >> name_map[*vBegin];
		compileCosts >> compile_cost_map[*vBegin];
	}
	typename boost::graph_traits<graph>::vertex_iterator it, itEnd;
	typename boost::graph_traits<graph>::adjacency_iterator aIterator, aIteratorEnd;
	for (boost::tie(it, itEnd) = vertices(g); it != itEnd; ++it) {
		color_map[*it] = boost::white_color;
	}
	for (boost::tie(it, itEnd) = vertices(g); it != itEnd; ++it) {
		for (boost::tie(aIterator, aIteratorEnd) = boost::adjacent_vertices(*it, g); aIterator != aIteratorEnd; ++aIterator) {
			color_map[*aIterator] = boost::black_color;
		}
	}


	for (boost::tie(it, itEnd) = vertices(g); it != itEnd; ++it) {
			if (color_map[*it] == boost::black_color) {
				distance_map[*it] = compile_cost_map[*it];
			}
			else {
				distance_map[*it] = compile_cost_map[*it];

			}
	}
	
	if (hasCycle(g, color_map)) {
		std::cout << "Cycle in graph detected\n";
		return 0;
	}
	std::vector<vertex_t> topoOrder(boost::num_vertices(g));
	topoSort(g, topoOrder.rbegin(), color_map);
	std::vector<vertex_t>::iterator vIterator;
	for (vIterator = topoOrder.begin(); vIterator != topoOrder.end(); ++vIterator) {
		vertex_t u = *vIterator;
		for (boost::tie(aIterator, aIteratorEnd) = adjacent_vertices(u, g); aIterator != aIteratorEnd; ++aIterator) {
			if (distance_map[*aIterator] < distance_map[u] + compile_cost_map[*aIterator]) {
				distance_map[*aIterator] = distance_map[u] + compile_cost_map[*aIterator];
			}
		}
	}
	typename boost::graph_property_iter_range<graph, boost::vertex_distance_t>::iterator beg, end;
	tie(beg, end) = boost::get_property_iter_range(g, boost::vertex_distance);
	std::cout << "Max parallel compillation time: " << *std::max_element(beg, end) <<'\n';*/
	return 0;
}

