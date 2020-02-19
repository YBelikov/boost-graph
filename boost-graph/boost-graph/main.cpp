#include "./headers/algorithms/TopoSort.h"

int main()
{
	
	std::string graphFile{ "./resources/graph.txt" };

	std::string namesFile{ "./resources/names.txt" };
	std::string costsFile{ "./resources/costs.txt" };

	graph g = fillGraph<graph>(graphFile);
	
	
	name_map_t name_map = get(boost::vertex_name, g);
	compile_cost_map_t compile_cost_map = get(boost::vertex_compile_cost, g);
	distance_map_t distance_map = get(boost::vertex_distance, g);
	color_map_t color_map = get(boost::vertex_color, g);

	std::vector<vertex_t> topoOrder{ num_vertices(g) };
	
	std::ifstream verticesNames(namesFile.c_str());
	std::ifstream compileCosts(costsFile.c_str());
	typename boost::graph_traits<graph>::vertex_iterator vBegin, vEnd;
	for (tie(vBegin, vEnd) = vertices(g); vBegin != vEnd; ++vBegin) {
		verticesNames >> name_map[*vBegin];
		compileCosts >> compile_cost_map[*vBegin];
	}
	
	boost::graph_property_iter_range<graph, boost::vertex_compile_cost_t>::iterator it, itEnd;
	tie(it, itEnd) = get_property_iter_range(g, boost::vertex_compile_cost);
	std::cout << "total time: " << std::accumulate(it, itEnd, 0.0) <<'\n';
	return 0;
}
