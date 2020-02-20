#pragma once
#include <boost/graph/graph_traits.hpp>
#include "./headers/DefaultVisitor.h"

template<typename Graph>
class CycleDetectionVisitor : public DefaultVisitor {
public:

	CycleDetectionVisitor(bool& cycle) : hasCycle{cycle}{}
	void backEdge(typename boost::graph_traits<Graph>::edge_descriptor edge, const Graph& g) {
		hasCycle = true;
	}
	bool doesGraphHasCycle() { return hasCycle; }
private:
	bool& hasCycle;
};